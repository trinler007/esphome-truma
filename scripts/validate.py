# SPDX-License-Identifier: GPL-3.0-only
# Copyright (c) 2026 trinler007
"""Validate shipped configurations against local components, without real secrets."""
import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compile", action="store_true", help="Build TruMatic firmware")
    args = parser.parse_args()
    configs = [p for p in ROOT.glob("*.yaml") if p.name != "secrets.example.yaml"]
    source = {"source": {"type": "local", "path": (ROOT / "components").as_posix()}}
    workspace = ROOT / ".validation"
    workspace.mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(dir=workspace) as temp:
        directory = Path(temp)
        for config in sorted(configs):
            contents = config.read_text(encoding="utf-8")
            # BLE examples intentionally ship with a device-address placeholder.
            contents = contents.replace("XX:XX:XX:XX:XX:XX", "02:00:00:00:00:01")
            # Replace only the root external_components block, preserving YAML tags/lambdas.
            contents, replaced = re.subn(
                r"(?m)^external_components:\n(?:^[ \t].*\n|^\n|^#.*\n)*",
                lambda _: yaml.safe_dump(
                    {"external_components": [source]}, sort_keys=False, allow_unicode=True
                ),
                contents,
                count=1,
            )
            if replaced != 1:
                raise RuntimeError(f"Missing external_components block: {config.name}")
            secrets = {}
            for key in re.findall(r"!secret\s+([\w_]+)", contents):
                secrets[key] = (
                    "AQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQE="
                    if "key" in key else "validation-placeholder"
                )
            (directory / "secrets.yaml").write_text(yaml.safe_dump(secrets), encoding="utf-8")
            target = directory / config.name
            target.write_text(contents, encoding="utf-8")
            print(f"Checking {config.name}", flush=True)
            subprocess.run([sys.executable, "-m", "esphome", "config", str(target)], check=True)
            command = [sys.executable, "-m", "esphome", "compile", str(target)]
            if not (args.compile and config.name == "trumatic.yaml"):
                command.append("--only-generate")
            subprocess.run(command, check=True)


if __name__ == "__main__":
    main()

