# MERROW: THE LOST PAGES

A single-player dark-fantasy adventure project targeting **Unreal Engine 5.6**.

## Current status

The initial C++ project scaffold and the first support system are in the repository:

- Unreal project descriptor: `Merrow.uproject`
- C++ game and editor targets
- Runtime module: `Merrow`
- `AMerrowAtmosphereDirector`: adjustable fog density and fog color, blending from a natural atmosphere toward emerald corruption

**Build status:** not compiled or tested in Unreal Editor yet. GitHub stores the source but does not compile Unreal Engine projects.

## Source layout

```
Merrow.uproject
Config/DefaultEngine.ini
Source/
  Merrow.Target.cs
  MerrowEditor.Target.cs
  Merrow/
    Merrow.Build.cs
    Merrow.h
    Merrow.cpp
    Atmosphere/
      MerrowAtmosphereDirector.h
      MerrowAtmosphereDirector.cpp
```

## Atmosphere director

Once the project is compiled in a compatible Unreal Engine 5.6 environment, add an **Merrow Atmosphere Director** actor to a level. Its Details panel exposes clean/corrupted fog density and color settings. Call `SetCorruptionIntensity(0.0 - 1.0)` from Blueprint or C++ to blend between the two states.

This is the first support system, not a finished visual environment. A level, player character, lighting, sky, foliage, materials, sound, and post-process setup still need to be created and tested.

## Story direction

Ancient Magic once helped shape the first life in Merrow. It fell dormant until something awakened it—and a foreign force infected it. A forbidden book was scattered across the land during the corruption. Its missing pages contain clues to the Entity's weakness and the ritual that may defeat it. Recovering every required page is essential.

The origin of the Corrupted King and its precise relationship to the Entity remain intentionally undecided.

## Build requirement

Opening and compiling the project requires Unreal Engine 5.6 and a compatible C++ build toolchain. The source can be edited on a Chromebook through GitHub, but a compatible Unreal environment is still needed to generate project files, compile, and play it.