# MERROW: THE LOST PAGES

A single-player dark-fantasy adventure project targeting **Unreal Engine 5.6**.

## Current project foundation

- Unreal project descriptor and C++ game/editor targets
- Runtime module: `Merrow`
- `AMerrowAtmosphereDirector`: adjustable fog density and colour, blending natural mist toward emerald corruption
- `AMerrowForestSceneDirector`: deterministic Ancient Forest blockout generator using Unreal's built-in basic meshes as temporary placeholders

**Build status:** source files have been committed, but the project has not yet been compiled or tested in Unreal Editor. GitHub stores the source; it does not compile Unreal projects.

## First environment blockout

Add a `MerrowForestSceneDirector` actor to an empty level. Its Details panel lets you tune tree count, rocks, ruin blocks, crystal count, forest radius, random seed, and corruption intensity. The actor rebuilds the layout when its properties change.

The generated geometry is deliberately a greybox: primitive meshes stand in for final art. The central clearing stays relatively open for a path, story discovery, or later boss arena; ruins and rocks are distributed through the forest; corruption crystals favour the outer ring.

For a polished environment, replace the placeholders with custom tree, rock, ruin, and crystal meshes; add landscape sculpting, foliage, materials, lighting, sky, sound, and post-processing. The generator is a layout aid, not a finished realistic forest.

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
    World/
      MerrowForestSceneDirector.h
      MerrowForestSceneDirector.cpp
```

## Story direction

Ancient Magic once helped shape the first life in Merrow. It fell dormant until something awakened it—and a foreign force infected it. A forbidden book was scattered across the land during the corruption. Its missing pages contain clues to the Entity's weakness and the ritual that may defeat it. Recovering every required page is essential.

The origin of the Corrupted King and its precise relationship to the Entity remain intentionally undecided.

## Build requirements

Opening and compiling the project requires Unreal Engine 5.6 and a compatible C++ build toolchain. The source can be edited on a Chromebook through GitHub, but a compatible Unreal environment is still needed to generate project files, compile, and play it.
