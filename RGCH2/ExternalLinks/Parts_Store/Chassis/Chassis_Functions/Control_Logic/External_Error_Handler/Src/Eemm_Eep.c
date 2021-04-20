/**
 *  @file       emm_eep.c
 *
 *  @brief      EEPROM Zugriff (Fehlerspeicher, Fehler Haeufigkeitszaehler) einer EMM Slave Task.
 *
 *
 *  @section    Historie
 *
 *  2012-12-07 / werner.unsinn@agcocorp.com
 *  - erstellt
 *
 *  2013-02-06 / werner.unsinn@agcocorp.com
 *  - Bug bzgl. der Anzahl der Fehler beim Auslesen der Haeufigkeitszaehler gefixed
 *
 *  2014-04-02 / Mattis Kornelius
 *  - [Misc] minor changes for better MISRA-C compliance
 */


#include "Eemm_Def.h"
#include "Eemm_Conf.h"
#include "Eemm.h"

#include "Eemm_Eep.h"

#include "Eos.h"



/**
 *  Liesst den Haeufigkeitszaehler fuer einen Fehler aus dem EEPROM.
 *
 *  @param location_u8  Fehlerort
 *  @return             Client
 */
static uint8 getClient_u8(uint8 location_u8);
static uint8 getClient_u8(uint8 location_u8)
{
    uint8 client_u8;

    for (client_u8 = 0u; client_u8 < EMM_CLIENT_MAX; client_u8++)
    {
        if (location_u8 == emmConfig_cs.client_as[client_u8].location_u8)
        {
            break;
        }
    }

    return client_u8;
}


/**
 *  Liesst den Haeufigkeitszaehler fuer einen Fehler aus dem EEPROM.
 *
 *  @param client_u8    Client
 *  @param code_u8      Fehlercode
 *  @return             Inhalt des Haeufigkeitszaehlers
 */
static uint8 readErrorCounter_u8(uint8 client_u8, uint8 code_u8);
static uint8 readErrorCounter_u8(uint8 client_u8, uint8 code_u8)
{
    uint8 counter_u8 = 0xFFu;

    uint16 addr_u16;
    addr_u16 = emmConfig_cs.client_as[client_u8].addrErrorCounter_u16;
    addr_u16 += code_u8;
    EosEepromRead_s32(addr_u16, &counter_u8, 1u);

    return counter_u8;
}


/**
 *  Beschreibt den Haeufigkeitszaehler fuer einen Fehler im EEPROM.
 *
 *  @param client_u8    Client
 *  @param code_u8      Fehlercode
 *  @param counter_u8   zu schreibender Wert fuer den Haeufigkeitszaehler
 */
static void writeErrorCounter(uint8 client_u8, uint8 code_u8, uint8 counter_u8);
static void writeErrorCounter(uint8 client_u8, uint8 code_u8, uint8 counter_u8)
{
    uint16 addr_u16;
    addr_u16 = emmConfig_cs.client_as[client_u8].addrErrorCounter_u16;
    addr_u16 += code_u8;
    EosEepromWrite_s32(addr_u16, &counter_u8, 1u);
}


/**
 *  Erhoeht den Haeufigkeitszaehler fuer einen Fehler im EEPROM.
 *  (der Zaehler kann maximal den Wert 254 annehmen)
 *
 *  @param client_u8    Client
 *  @param code_u8      Fehlercode
 */
static void incErrorCounter(uint8 client_u8, uint8 code_u8);
static void incErrorCounter(uint8 client_u8, uint8 code_u8)
{
    uint8 counter_u8;

    counter_u8 = readErrorCounter_u8(client_u8, code_u8);
    if (counter_u8 == 255u)
    {
        counter_u8 = 0u;
    }

    counter_u8++;
    if (counter_u8 > 254u)
    {
        counter_u8 = 254u;
    }

    writeErrorCounter(client_u8, code_u8, counter_u8);
}


/**
 *  Liesst den Zeiger auf den zuletzt abgesetzten Fehler aus dem EEPROM.
 *
 *  @return             Zeiger auf den zuletzt abgesetzten Fehler
 */
static uint16 readErrorStoragePointer_u16(void);
static uint16 readErrorStoragePointer_u16(void)
{
    uint16 pointer_u16;

    uint16 addr_u16;
    addr_u16 = emmConfig_cs.addrErrorStorrage_u16 + 0u;
    EosEepromRead_s32(addr_u16, (uint8*) &pointer_u16, 2u);

    if (pointer_u16 > (uint8)(emmConfig_cs.numErrorStorrageEntries_u8 - 1u))
    {
        pointer_u16 = (uint8)(emmConfig_cs.numErrorStorrageEntries_u8 - 1u);
    }
    return pointer_u16;
}


/**
 *  Beschreibt den Zeiger auf den zuletzt abgesetzten Fehler aus dem EEPROM.
 *
 *  @param pointer_u16  Zeiger auf den zuletzt abgesetzten Fehler
 */
static void writeErrorStoragePointer(uint16 pointer_u16);
static void writeErrorStoragePointer(uint16 pointer_u16)
{
    uint16 addr_u16;
    addr_u16 = emmConfig_cs.addrErrorStorrage_u16 + 0u;
    EosEepromWrite_s32(addr_u16, (uint8*) &pointer_u16, 2u);
}


/**
 *  Liesst die laufende Nummer des zuletzt abgesetzten Fehlers aus dem EEPROM.
 *
 *  @return             laufende Nummer des zuletzt abgesetzten Fehlers
 */
static uint8 readErrorStorageSerial_u8(void);
static uint8 readErrorStorageSerial_u8(void)
{
    uint8 serial_u8 = 0x00u;

    uint16 addr_u16;
    addr_u16 = emmConfig_cs.addrErrorStorrage_u16 + 2u;
    EosEepromRead_s32(addr_u16, &serial_u8, 1u);

    return serial_u8;
}


/**
 *  Beschreibt die laufende Nummer fuer den zuletzt abgesetzten Fehlers im EEPROM.
 *
 *  @param serial_u8    laufende Nummer des zuletzt abgesetzten Fehlers
 */
static void writeErrorStorageSerial(uint8 serial_u8);
static void writeErrorStorageSerial(uint8 serial_u8)
{
    uint16 addr_u16;
    addr_u16 = emmConfig_cs.addrErrorStorrage_u16 + 2u;
    EosEepromWrite_s32(addr_u16, &serial_u8, 1u);
}


/**
 *  Erhoeht die laufende Nummer der Fehler im EEPROM.
 *
 *  @return             laufende Nummer fuer einen neuen Fehler
 */
static uint8 incErrorStorageSerial_u8(void);
static uint8 incErrorStorageSerial_u8(void)
{
    uint8 serial_u8;

    serial_u8 = readErrorStorageSerial_u8();

    if (serial_u8 == 0xFFu)
    {
        serial_u8 = 0x00u;
    }

    serial_u8++;

    writeErrorStorageSerial(serial_u8);

    return serial_u8;
}


/**
 *  Liesst einen Eintrag des Fehlerspeichers aus dem EEPROM.
 *
 *  @param pointer_u16  Zeiger auf den zu lesenden Eintrag
 *  @param entry_ps     Struktur des Eintrags in die gelesen wird
 */
static void readErrorStorageEntry(uint16 pointer_u16, EmmStorageEntry_ts* entry_ps);
static void readErrorStorageEntry(uint16 pointer_u16, EmmStorageEntry_ts* entry_ps)
{
    uint16 addr_u16;
    addr_u16 = emmConfig_cs.addrErrorStorrage_u16 + 16 + pointer_u16 * sizeof(EmmStorageEntry_ts);

    EosEepromRead_s32(addr_u16, (uint8*) entry_ps, sizeof(EmmStorageEntry_ts));
}


/**
 *  Beschreibt einen Eintrag des Fehlerspeichers im EEPROM.
 *
 *  @param pointer_u16  Zeiger auf den zu beschreibenden Eintrag
 *  @param entry_ps     Struktur des Eintrags aus der gelesen wird
 */
static void writeErrorStorageEntry(uint16 pointer_u16, const EmmStorageEntry_ts* entry_ps);
static void writeErrorStorageEntry(uint16 pointer_u16, const EmmStorageEntry_ts* entry_ps)
{
    uint16 addr_u16;
    addr_u16 = (uint16) ((emmConfig_cs.addrErrorStorrage_u16 + 16u + (pointer_u16 * sizeof(EmmStorageEntry_ts))) & MAXUINT16);

    // Ausgabe der Warnung "division by zero", wenn Strukturgroesse != 16
    if (1u / ((sizeof(EmmStorageEntry_ts) - 16u) ? 0u : 1u)) { }

    EosEepromWrite_s32(addr_u16, (uint8*) entry_ps, sizeof(EmmStorageEntry_ts));
}


/**
 *  Fuegt einen Eintrag zum Fehlerspeichers im EEPROM hinzu.
 *
 *  @param entry_ps     Struktur des Eintrags der hinzugefuegt wird
 */
static void addErrorStorageEntry(EmmStorageEntry_ts* entry_ps);
static void addErrorStorageEntry(EmmStorageEntry_ts* entry_ps)
{
    EmmStorageEntry_ts lastEntry_s;
    uint16 pointer_u16;

#if 1

    pointer_u16 = readErrorStoragePointer_u16();

    readErrorStorageEntry(pointer_u16, &lastEntry_s);

    if ((lastEntry_s.location_u8 == entry_ps->location_u8) &&
        (lastEntry_s.code_u8 == entry_ps->code_u8)         &&
        (lastEntry_s.counter_u8 < 255u))
    {
        // letzten Fehler ueberschreiben -> Zaehler erhoehen
        entry_ps->counter_u8 = lastEntry_s.counter_u8 + 1;

        if (entry_ps->counter_u8 > 254u)
        {
            entry_ps->counter_u8 = 254u;
        }
    }
    else
    {
        // Fehler in naechste Zeile schreiben
        pointer_u16++;
        if (pointer_u16 > (uint8)(emmConfig_cs.numErrorStorrageEntries_u8 - 1u))
        {
            pointer_u16 = 0u;
        }
        writeErrorStoragePointer(pointer_u16);
    }
    writeErrorStorageEntry(pointer_u16, entry_ps);

#else

    uint16 lastPointer_u16;

    pointer_u16 = readErrorStoragePointer_u16();

    lastPointer_u16 = pointer_u16;
    do
    {
        readErrorStorageEntry(lastPointer_u16, &lastEntry_s);

        if ((lastEntry_s.location_u8 == entry_ps->location_u8) && (lastEntry_s.code_u8 == entry_ps->code_u8))
        {
            break;
        }

        if (lastPointer_u16 == 0u)
        {
            lastPointer_u16 = emmConfig_cs.numErrorStorrageEntries_u8;
        }
        lastPointer_u16--;
    }
    while (lastPointer_u16 != pointer_u16);


    if ((lastEntry_s.location_u8 == entry_ps->location_u8) &&
        (lastEntry_s.code_u8 == entry_ps->code_u8)         &&
        (lastEntry_s.counter_u8 < 255u)                    &&
        ((lastEntry_s.starts_u16 == entry_ps->starts_u16) || (lastEntry_s.starts_u16 == entry_ps->starts_u16 - 1u)))
    {
        // letzten Fehler ueberschreiben
        pointer_u16 = lastPointer_u16;

        // Zaehler erhoehen
        entry_ps->counter_u8 = lastEntry_s.counter_u8 + 1u;
    }
    else
    {
        // Fehler in naechste Zeile schreiben
        pointer_u16++;
        if (pointer_u16 > (uint8)(emmConfig_cs.numErrorStorrageEntries_u8 - 1u))
        {
            pointer_u16 = 0u;
        }
        writeErrorStoragePointer(pointer_u16);
    }
    writeErrorStorageEntry(pointer_u16, entry_ps);

#endif
}


/**
 *  Liesst den Kaltstartzaehler aus dem EEPROM.
 *
 *  @return             Wert des Kaltstartzaehlers
 */
static uint16 readStartCounter_u16(void);
static uint16 readStartCounter_u16(void)
{
    static boolean first_b = TRUE;
    static uint16 counter_u16 = 0x0000u;

    if (first_b)
    {
        uint16 addr_u16;
        addr_u16 = emmConfig_cs.addrStartCounter_u16;
        EosEepromRead_s32(addr_u16, (uint8*) &counter_u16, 2u);

        first_b = FALSE;
    }

    return counter_u16;
}





/**
 *  Speichert einen Fehler im Fehlerspeicher.
 *
 *  @param client_u8    Client
 *  @param code_u8      Fehlercode
 *  @param data1_u16    1. individueller Wert der im Fehlerspeicher mit abgespeichert wird
 *  @param data2_u16    2. individueller  Wert der im Fehlerspeicher mit abgespeichert wird
 *  @return             laufende Nummer des Fehlers im Fehlerspeicher
 */
uint8 saveError_u8(uint8 client_u8, uint8 code_u8, uint16 data1_u16, uint16 data2_u16)
{
    EmmStorageEntry_ts entry_s;
    EosAiStatus_ts ai_s;
    sint32 err_s32 = EosAiGetSt_s32(AI_VBAT, &ai_s);


    // Haeufigkeitszaehler erhoehen
    incErrorCounter(client_u8, code_u8);


    // Fehler in den Fehlerspeicher eintragen
    entry_s.location_u8 = emmConfig_cs.client_as[client_u8].location_u8;
    entry_s.code_u8 = code_u8;
    entry_s.counter_u8 = 0x01u;
    entry_s.serial_u8 = incErrorStorageSerial_u8();


    entry_s.data1_u16 = data1_u16; // 1. Individueller Wert
    entry_s.data2_u16 = data2_u16; // 2. Individueller Wert

    if (err_s32 == 0)
    {
        entry_s.ub_u16 = (uint16) ai_s.volt_mV_u32;
    }
    else
    {
        entry_s.ub_u16 = 0u; // keine Betriebsspannung verfuegbar
    }

    entry_s.ticks_u32 = PxTickGetCount();
    entry_s.starts_u16 = readStartCounter_u16();



    addErrorStorageEntry(&entry_s);

    return entry_s.serial_u8;
}


/**
 *  Auslesen der Haeufigkeitszaehler.
 *  Die Inhalte der Haeufigkeitszaehler werden in den uebergebenen Speicherbereich geschrieben:
 *  - Byte 0: Anzahl der Fehler (High Byte)
 *  - Byte 1: Anzahl der Fehler (Low Byte)
 *  - Byte 2: Fehlerort                     \
 *  - Byte 3: Fehlercode                    > Eintrag 1
 *  - Byte 4: Haeufigkeitszaehler           /
 *  - Byte 5: Fehlerort                     \
 *  - Byte 6: Fehlercode                    > Eintrag 2
 *  - Byte 7: Haeufigkeitszaehler           /
 *    ...
 *  - Byte n-3: Fehlerort                   \
 *  - Byte n-2: Fehlercode                  > Eintrag m
 *  - Byte n-1: Haeufigkeitszaehler         /
 *
 *  Anmerkung: Es werden maximal 256 Haeufigkeitszaehler ausgegeben.
 *
 *  @param data_pu8     Zeiger auf Speicherbereich in den die Inhalte der Haeufigkeitszaehler kopiert werden
 *  @param n_u16        Anzahl der Bytes die maximal zur Verfuegung stehen
 *  @return             Anzahl n der Byte die im Speicherbereich benoetigt wurden (bzw. benoetigt werden wuerden)
 */
uint16 readErrorCounters_u16(uint8* data_pu8, uint16 n_u16)
{
    uint8   client_u8;
    uint16  code_u16;
    uint8   counter_u8;
    uint16  index_u16;

    index_u16 = 2u;

    for (client_u8 = 0u; client_u8 < EMM_CLIENT_MAX; client_u8++)
    {
        for (code_u16 = 0u; code_u16 < ((uint16) emmConfig_cs.client_as[client_u8].maxErrorCode_u8 + 1u); code_u16++)
        {
            counter_u8 = readErrorCounter_u8(client_u8, (uint8) code_u16);
            if (counter_u8 == 255u)
            {
                counter_u8 = 0u;
            }

            if (counter_u8 > 0u)
            {
                if ((index_u16 + 2u) < n_u16)
                {
                    data_pu8[index_u16 + 0] = emmConfig_cs.client_as[client_u8].location_u8;
                    data_pu8[index_u16 + 1] = (uint8) code_u16;
                    data_pu8[index_u16 + 2] = counter_u8;
                }
                index_u16 += 3u;
            }
        }
    }

    if (n_u16 >= 2u)
    {
        uint16 i_u16 = (index_u16 - 2u) / 3u;
        data_pu8[0] = (uint8) (i_u16 >> 8) & 0xFFu;
        data_pu8[1] = (uint8)  i_u16       & 0xFFu;
    }
    return index_u16;
}


/**
 *  Auslesen des Fehlerspeichers.
 *  Der Inhalt des Fehlerspeichers wird in den uebergebenen Speicherbereich geschrieben:
 *  - Byte  0: Anzahl der Fehler
 *  - Byte  1: Speicherplatznummer                  \
 *  - Byte  2: Fehlerort                            |
 *  - Byte  3: Fehlercode                           > Eintrag 1
 *  - Byte  4: laufende Nummer des Fehlers          |
 *  - Byte  5: Fehlerstatus                         |
 *  - Byte  6: Fehlerhaeufigkeit                    /
 *  - Byte  7: Speicherplatznummer                  \
 *  - Byte  8: Fehlerort                            |
 *  - Byte  9: Fehlercode                           > Eintrag 2
 *  - Byte 10: laufende Nummer des Fehlers          |
 *  - Byte 11: Fehlerstatus                         |
 *  - Byte 12: Fehlerhaeufigkeit                    /
 *    ...
 *  - Byte n-6: Speicherplatznummer                 \
 *  - Byte n-5: Fehlerort                           |
 *  - Byte n-4: Fehlercode                          > Eintrag m
 *  - Byte n-3: laufende Nummer des Fehlers         |
 *  - Byte n-2: Fehlerstatus                        |
 *  - Byte n-1: Fehlerhaeufigkeit                   /
 *
 *  @param data_pu8     Zeiger auf Speicherbereich in den der Inhalt des Fehlerspeichers kopiert wird
 *  @param n_u16        Anzahl der Bytes die maximal zur Verfuegung stehen
 *  @return             Anzahl n der Byte die im Speicherbereich benoetigt wurden (bzw. benoetigt werden wuerden)
 */
uint16 readErrorStorage_u16(uint8* data_pu8, uint16 n_u16)
{
    EmmStorageEntry_ts entry_s;
    uint16 pointer1st_u16;
    uint16 pointer_u16;
    uint16 index_u16;

    index_u16 = 1u;

    // beginnen mit dem letzten abgesetzten Fehler
    pointer1st_u16 = pointer_u16 = readErrorStoragePointer_u16();

    while (pointer_u16 < emmConfig_cs.numErrorStorrageEntries_u8)
    {
        readErrorStorageEntry(pointer_u16, &entry_s);

        if (entry_s.location_u8 >= 64u)
        {
            break;
        }

        if ((index_u16 + 5u) < n_u16)
        {
            boolean active_b;
            active_b = isErrorActive_b(getClient_u8(entry_s.location_u8), entry_s.code_u8);

            data_pu8[index_u16 + 0] = (uint8) pointer_u16;                                // Speicherplatznummer

            data_pu8[index_u16 + 1] = entry_s.location_u8;                                // Fehlerort
            data_pu8[index_u16 + 2] = entry_s.code_u8;                                    // Fehlercode
            data_pu8[index_u16 + 3] = entry_s.serial_u8;                                  // laufende Fehlernummer
            data_pu8[index_u16 + 4] = (active_b) ? 0x01u : 0x00u;                         // Fehlerstatus (Aktiv)
            data_pu8[index_u16 + 5] = entry_s.counter_u8;                                 // Fehlerhaeufigkeit
        }
        index_u16 += 6u;

        if (pointer_u16 == 0u)
        {
            // nach erstem Eintrag im Fehlerspeicher nochmal von hinten beginnen
            pointer_u16 = emmConfig_cs.numErrorStorrageEntries_u8;
        }
        pointer_u16--;

        if (pointer_u16 == pointer1st_u16)
        {
            // jetzt waere ich wieder da wo ich angefangen habe - "aus is"
            pointer_u16 = emmConfig_cs.numErrorStorrageEntries_u8; // -> while()-Schleife beenden
        }
    }

    if (n_u16 >= 1u)
    {
        data_pu8[0] = (uint8) (((index_u16 - 1u) / 6u) & MAXUINT8);
    }
    return index_u16;
}


/**
 *  Auslesen der Umgebungsvariablen fuer einen Eintrag im Fehlerspeicher.
 *  Der Inhalt des Fehlerspeichers wird in den uebergebenen Speicherbereich geschrieben:
 *  - Byte  0: Fehlerort
 *  - Byte  1: Fehlercode
 *  - Byte  2: laufende Nummer des Fehlers
 *  - Byte  3: Fehlerstatus (Aktiv)
 *  - Byte  4: Fehlerhaeufigkeit
 *  - Byte  5: Anzahl der Umgebungsvariablen
 *  - Byte  6: Datentype             \
 *  - Byte  7: Wert (High Byte)      |
 *  - Byte  8: Wert                  > Umgebungsvariable 1
 *  - Byte  9: Wert                  |
 *  - Byte 10: Wert (Low Byte)       /
 *  - Byte 11: Datentype             \
 *  - Byte 12: Wert (High Byte)      |
 *  - Byte 13: Wert                  > Umgebungsvariable 2
 *  - Byte 14: Wert                  |
 *  - Byte 15: Wert (Low Byte)       /
 *    ...
 *  - Byte n-5: Datentype            \
 *  - Byte n-4: Wert (High Byte)     |
 *  - Byte n-3: Wert                 > Umgebungsvariable m
 *  - Byte n-2: Wert                 |
 *  - Byte n-1: Wert (Low Byte)      /
 *
 *  @param i_u16        Nummer des Eintrags im Fehlerspeicher (Speicherplatznummer)
 *  @param data_pu8     Zeiger auf Speicherbereich in den die Umgebungsvariablen fuer den Eintrag kopiert werden
 *  @param n_u16        Anzahl der Bytes die maximal zur Verfuegung stehen
 *  @return             Anzahl n der Byte die im Speicherbereich benoetigt wurden (bzw. benoetigt werden wuerden)
 *                      (-1 wenn das Auslesen der Umgebungsvariablen fuer den Eintrag nicht erfolgreich)
 */
sint32 readEnvironmentValues_s32(uint16 i_u16, uint8* data_pu8, uint16 n_u16)
{
    EmmStorageEntry_ts entry_s;
    sint32 size_s32;

    if ((i_u16 < emmConfig_cs.numErrorStorrageEntries_u8) && (n_u16 >= (6u + (5u * 5u))))
    {
        readErrorStorageEntry(i_u16, &entry_s);

        if ((entry_s.location_u8 < 64u))
        {
            boolean active_b;
            active_b = isErrorActive_b(getClient_u8(entry_s.location_u8), entry_s.code_u8);

            data_pu8[0] = entry_s.location_u8;
            data_pu8[1] = entry_s.code_u8;
            data_pu8[2] = entry_s.serial_u8;
            data_pu8[3] = (active_b) ? 0x01u : 0x00u;
            data_pu8[4] = entry_s.counter_u8;
            data_pu8[5] = 5u; // Anzahl der Umgebungsvariablen

            data_pu8[6 + 0 * 5 + 0] = 0u;  // 1. Individueller Wert
            data_pu8[6 + 0 * 5 + 1] = 0u;
            data_pu8[6 + 0 * 5 + 2] = 0u;
            data_pu8[6 + 0 * 5 + 3] = (uint8) (entry_s.data1_u16 >> 8) & 0xFFu;
            data_pu8[6 + 0 * 5 + 4] = (uint8)  entry_s.data1_u16       & 0xFFu;

            data_pu8[6 + 1 * 5 + 0] = 39u; // 2. Individueller Wert
            data_pu8[6 + 1 * 5 + 1] = 0u;
            data_pu8[6 + 1 * 5 + 2] = 0u;
            data_pu8[6 + 1 * 5 + 3] = (uint8) (entry_s.data2_u16 >> 8) & 0xFFu;
            data_pu8[6 + 1 * 5 + 4] = (uint8)  entry_s.data2_u16       & 0xFFu;

            data_pu8[6 + 2 * 5 + 0] = 38u; // Versorgungsspannung
            data_pu8[6 + 2 * 5 + 1] = 0u;
            data_pu8[6 + 2 * 5 + 2] = 0u;
            data_pu8[6 + 2 * 5 + 3] = (uint8) (entry_s.ub_u16 >> 8) & 0xFFu;
            data_pu8[6 + 2 * 5 + 4] = (uint8)  entry_s.ub_u16       & 0xFFu;

            data_pu8[6 + 3 * 5 + 0] = 36u; // Kaltstartzaehler
            data_pu8[6 + 3 * 5 + 1] = 0u;
            data_pu8[6 + 3 * 5 + 2] = 0u;
            data_pu8[6 + 3 * 5 + 3] = (uint8) (entry_s.starts_u16 >> 8) & 0xFFu;
            data_pu8[6 + 3 * 5 + 4] = (uint8)  entry_s.starts_u16       & 0xFFu;

            data_pu8[6 + 4 * 5 + 0] = 37u; // Millisekundenzaehler (PXROS)
            data_pu8[6 + 4 * 5 + 1] = (uint8) (entry_s.ticks_u32 >> 24) & 0xFFu;
            data_pu8[6 + 4 * 5 + 2] = (uint8) (entry_s.ticks_u32 >> 16) & 0xFFu;
            data_pu8[6 + 4 * 5 + 3] = (uint8) (entry_s.ticks_u32 >>  8) & 0xFFu;
            data_pu8[6 + 4 * 5 + 4] = (uint8)  entry_s.ticks_u32        & 0xFFu;

            size_s32 = (6u + (5u * 5u));
        }
        else
        {
            size_s32 = -1; // Eintrag noch nicht befuellt
        }
    }
    else
    {
        size_s32 = -1; // ungueltige Eintragnummer
    }
    return size_s32;
}


/**
 *  Loescht die Haeufigkeitszaehler im EEPROM.
 *
 *  @return             0 wenn das Loeschen erfolgreich war, sonst != 0
 */
sint32 clearErrorCounters_s32(void)
{
    uint8 client_u8;
    sint32 err_s32;

    for (client_u8 = 0u; client_u8 < EMM_CLIENT_MAX; client_u8++)
    {
        uint16 addr_u16;
        uint16 size_u16;
        addr_u16 = emmConfig_cs.client_as[client_u8].addrErrorCounter_u16;
        size_u16 = (uint16) emmConfig_cs.client_as[client_u8].maxErrorCode_u8 + 1;

        err_s32 = EosEepromFill_s32(addr_u16, 0xFFu, size_u16);
    }
    return err_s32;
}


/**
 *  Loescht die Eintraege des Fehlerspeichers im EEPROM.
 *
 *  @return             0 wenn das Loeschen erfolgreich war, sonst != 0
 */
sint32 clearErrorStorage_s32(void)
{
    uint16 addr_u16;
    uint16 size_u16;
    sint32 err_s32;

    addr_u16 = emmConfig_cs.addrErrorStorrage_u16 + 0u;
    size_u16 = 16 + emmConfig_cs.numErrorStorrageEntries_u8 * sizeof(EmmStorageEntry_ts);

    err_s32 = EosEepromFill_s32(addr_u16, 0xFFu, size_u16);

    return err_s32;
}
