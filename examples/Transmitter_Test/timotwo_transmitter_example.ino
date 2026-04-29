/**
 * timotwo_example.ino
 * ─────────────────────────────────────────────────────────────
 *  Bare-metal Lumenradio Timotwo usage example and test env
 *  for Radical Wireless LUMEN CONTROL
 *  Include timotwo_driver.h in the same sketch folder
 *  Author: Stefan Graf stefan@graf-lichtechnik.de
 *  check at https://www.radicalwireless.com
 *  or
 *  https://www.tinkerberg.com
 *  for more details
 * ─────────────────────────────────────────────────────────────
 */

#include "timotwo_driver.h"

// ── DMX universe ──────────────────────────────────────────────
static uint8_t dmx[512] = {};

void setup() {
    Serial.begin(115200);
    delay(400);

    timoBegin();
    delay(300);  // allow module to boot

    // Verify module is present
    if (!timoDetect()) {
        Serial.println("ERROR: TimoTwo not found — check wiring");
        while (true) delay(1000);
    }
    timoPrintVersion();

    // Set OEM info — model 0x0001, ESTA manufacturer ID 0x08B6
    timoSetOEMInfo(0x6000, 0x08B6);

    // Set device name
    timoSetDeviceName("LUMEN CONTROL L10231");

    // Set universe color (optional — visible in CRMX app)
    timoSetUniverseColor(0xFF, 0x80, 0x00);  // orange

    // Init TX mode: CRMX, 512 channels, 40 Hz
    if (!timoConfigTX(TIMO_RF_CRMX, 512, 25000)) {
        Serial.println("ERROR: TX config failed");
        while (true) delay(1000);
    }

    Serial.println("Ready — press LINK button on module to pair");
}

void loop() {
    // ── Example: simple DMX fade on channels 1–16 ─────────────
    static uint8_t  level = 0;
    static int8_t   dir   = 1;
    static uint32_t lastTx = 0;

    if (millis() - lastTx >= 25) {  // ~40 Hz
        lastTx = millis();

        for (int i = 0; i < 16; i++) dmx[i] = level;
        timoWriteDMX(dmx, 512);

        level += dir * 3;
        if (level >= 252) dir = -1;
        if (level <= 3)   dir =  1;
    }

    // ── Periodic status output ────────────────────────────────
    static uint32_t lastStatus = 0;
    if (millis() - lastStatus >= 2000) {
        lastStatus = millis();
        Serial.printf("Linked: %s  RF: %s  Quality: %d  Level: %d\n",
            timoIsLinked()   ? "yes" : "no",
            timoHasRFLink()  ? "yes" : "no",
            timoLinkQuality(),
            level);
    }
}
