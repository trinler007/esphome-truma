# Herkunft und Weiterpflege / Provenance and maintenance

Stand / Snapshot: **2026-10-14**.

Die Basis ist [havanti/esphome-truma](https://github.com/havanti/esphome-truma),
Version **1.0.43**, Commit `2edc8d5387b46a2d36317006d3d84fe00c8010d5`.
Sie passt zur bestehenden ESP32-/ESP-IDF-Konfiguration und enthält unter anderem
Diesel-Energiemix, Aventa, Cooler, CP Plus C3 und die aktuellen Uhr-/Climate-Fixes.
Das ist eine begründete Basiswahl, keine Behauptung, sämtliche Forks seien vollständig integriert.

The base is Havanti **1.0.43** at the commit above. It fits the supplied ESP32 /
ESP-IDF configuration. This is a documented base selection, not a claim that
every feature from every fork has been integrated.

## Geprüfte Alternativen / Reviewed alternatives

GitHub fork lists and comparisons were retrieved on the snapshot date.

| Repository | Befund / Finding |
| --- | --- |
| Fabian-Schmidt/esphome-truma_inetbox | Original GPLv3 source; retained separately with its author history. |
| magior/esphome-truma | No commits ahead of Havanti main; 6 behind. CP Plus C3 contribution is already included. |
| franzBucher/esphome-truma | No commits ahead; 16 behind. |
| Harry-58/esphome-truma | No commits ahead; 59 behind. |
| Daswomo/esphome-truma | 8 commits ahead, 70 behind; experimental ventilation controls. Not merged without protocol/hardware verification. |
| kamahat/esphome-truma | GitHub comparison reports no common ancestor; not merged. |
| zorrobyte/esphome-truma2TPMS | GitHub comparison reports no common ancestor; not merged. |
| juvander/esphome-truma_inetbox | 50 commits ahead of the original; Arduino 3 and ESPHome compatibility work, separate implementation. No blind merge into the ESP-IDF base. |

Die Fork-Liste des ursprünglichen Projekts enthielt 33 Einträge; nicht jeder
Fork wurde auf Protokollebene geprüft. Ein neueres Push-Datum allein beweist
weder zusätzliche Funktionen noch Kompatibilität.

The original project's fork list contained 33 entries. Not every fork was
audited at protocol level. Push dates alone do not establish feature coverage
or compatibility.

## Historie / History

Havanti hat eine eigenständige Git-Historie ab 2026-04-23; sie hat keinen
gemeinsamen Git-Vorfahren mit dem Original. `main` erhält diese Historie ohne
Squash. `codex/original-upstream` erhält die originale Historie separat.
Die ursprünglichen Release-Tags werden mit übernommen und bezeichnen weiterhin
unveränderte Havanti-Stände, nicht neue Releases dieses Projekts.

Havanti's independent history starts on 2026-04-23 and has no common ancestor
with the original. `main` retains that history without squashing.
`codex/original-upstream` preserves the original history separately. Imported
tags continue to identify unchanged Havanti snapshots, not new releases here.

## Künftige Updates / Future updates

```sh
git remote add havanti https://github.com/havanti/esphome-truma.git
git remote add upstream https://github.com/Fabian-Schmidt/esphome-truma_inetbox.git
git fetch havanti --tags
git fetch upstream
git log --oneline main..havanti/main
git diff main...havanti/main -- components
```

Remotes nur anlegen, wenn sie noch fehlen. Änderungen auf einem `codex/`-Branch
prüfen, Attribution beibehalten, lokale URL-Anpassungen beim Merge erhalten,
`python scripts/validate.py` ausführen und am eigenen LIN-Bus testen.
Ein geprüfter Stand kann in `external_components.source.ref` auf einen Tag
oder Commit festgelegt werden; `refresh: 0s` folgt ansonsten der aktuellen Branch-Spitze.

Only add missing remotes. Review updates on a `codex/` branch, retain notices
and local repository URLs, run validation and test on the actual LIN bus.
Pin a reviewed tag or commit using `external_components.source.ref` when desired.

## Prüfung / Validation

```sh
python -m pip install esphome==2026.9.1
python scripts/validate.py
# Full ESP32 firmware build (also performed in GitHub Actions):
python scripts/validate.py --compile
```

Der Prüflauf verwendet lokale Komponenten und öffentliche Dummy-Secrets in
temporären Dateien; die ausgelieferte YAML bleibt auf dieses Repository gerichtet.
Schema und C++-Generierung prüfen die Konfiguration. Ein erfolgreicher Build
ersetzt keine Prüfung der Truma-Hardware. `HEATER_MAINS_POWER` bleibt experimentell.

Validation uses local components and dummy credentials in temporary files.
The shipped YAML continues to reference this repository. Schema checks, code
generation and firmware builds do not establish actual Truma hardware behavior.
`HEATER_MAINS_POWER` remains experimental.

