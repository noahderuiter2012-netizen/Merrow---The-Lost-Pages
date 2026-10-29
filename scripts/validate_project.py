#!/usr/bin/env python3
"""Structural sanity checks for the Merrow Unreal project (not an Unreal C++ build)."""
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
errors = []
warnings = []

def require_file(relative):
    if not (ROOT / relative).is_file():
        errors.append(f"Missing required file: {relative}")

project_path = ROOT / "Merrow.uproject"
try:
    project = json.loads(project_path.read_text(encoding="utf-8"))
    if project.get("EngineAssociation") != "5.6":
        errors.append("Merrow.uproject must target Unreal Engine 5.6.")
    modules = {m.get("Name") for m in project.get("Modules", [])}
    if "Merrow" not in modules:
        errors.append("Merrow runtime module is not declared.")
except Exception as exc:
    errors.append(f"Merrow.uproject is not valid JSON: {exc}")

required = [
    "Source/Merrow/Merrow.Build.cs",
    "Source/Merrow/Merrow.cpp",
    "Source/Merrow/Merrow.h",
    "Source/Merrow/Gameplay/MerrowPlayerCharacter.h",
    "Source/Merrow/Gameplay/MerrowPlayerCharacter.cpp",
    "Source/Merrow/Gameplay/MerrowLostPagePickup.h",
    "Source/Merrow/Gameplay/MerrowLostPagePickup.cpp",
    "Source/Merrow/Gameplay/MerrowAncientGate.h",
    "Source/Merrow/Gameplay/MerrowAncientGate.cpp",
    "Source/Merrow/Gameplay/MerrowHUD.h",
    "Source/Merrow/Gameplay/MerrowHUD.cpp",
    "Source/Merrow/Gameplay/MerrowGameMode.h",
    "Source/Merrow/Gameplay/MerrowGameMode.cpp",
    "Source/Merrow/World/MerrowForestSceneDirector.h",
    "Source/Merrow/World/MerrowForestSceneDirector.cpp",
    "Config/DefaultEngine.ini",
    "Config/DefaultInput.ini",
    "docs/index.html",
]
for path in required:
    require_file(path)

for header in ROOT.glob("Source/Merrow/**/*.h"):
    text = header.read_text(encoding="utf-8")
    generated = f'{header.stem}.generated.h'
    if "UCLASS" in text and generated not in text:
        errors.append(f"UCLASS header lacks its generated header include: {header.relative_to(ROOT)}")

input_config = (ROOT / "Config/DefaultInput.ini").read_text(encoding="utf-8") if (ROOT / "Config/DefaultInput.ini").exists() else ""
for mapping in ('AxisName="MoveForward"', 'AxisName="MoveRight"', 'AxisName="Turn"', 'AxisName="LookUp"', 'ActionName="Interact"', 'ActionName="Sprint"'):
    if mapping not in input_config:
        errors.append(f"Missing input mapping: {mapping}")

engine_config = (ROOT / "Config/DefaultEngine.ini").read_text(encoding="utf-8") if (ROOT / "Config/DefaultEngine.ini").exists() else ""
if "GlobalDefaultGameMode=/Script/Merrow.MerrowGameMode" not in engine_config:
    errors.append("Default GameMode is not configured in Config/DefaultEngine.ini.")

if not (ROOT / "Source/Merrow/Gameplay/MerrowAncientGate.cpp").exists():
    warnings.append("Gate interaction is not present; chapter cannot be completed.")

if errors:
    print("MERROW STRUCTURAL CHECKS FAILED")
    for error in errors:
        print(f"ERROR: {error}")
    sys.exit(1)

print(f"MERROW STRUCTURAL CHECKS PASSED ({len(required)} required paths checked)")
print("Note: this validates project structure only; it does not compile Unreal C++.")
for warning in warnings:
    print(f"WARNING: {warning}")
