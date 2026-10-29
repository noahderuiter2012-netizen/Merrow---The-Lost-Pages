# MERROW: THE LOST PAGES

A single-player dark-fantasy adventure project targeting **Unreal Engine 5.6**.

## Current project foundation

- Unreal project descriptor and C++ game/editor targets.
- `AMerrowAtmosphereDirector`: adjustable fog density and colour, blending natural mist toward emerald corruption.
- `AMerrowForestSceneDirector`: deterministic Ancient Forest blockout generator using Unreal's built-in primitive meshes as temporary placeholders.
- Forest layout includes a broad ground plane, tall tree silhouettes, scattered rocks and ruin blocks, a broken ancient path into the forest, and corruption crystals concentrated around the outer ring.
- `AMerrowDiscoveryLandmark`: editor-placeable greybox markers for lost-page shrines, lore relics, corruption scars, ancient gates, and boss arenas. Each marker has editable story clue text and an optional lost-page index.
- Adjustable counts, forest radius, random seed, and corruption intensity are exposed in the forest director's Details panel.

## Try the forest blockout

1. Open the project in **Unreal Engine 5.6** on a compatible Windows development computer with the C++ toolchain installed.
2. Open or create an empty level.
3. Add an `AMerrowForestSceneDirector` actor to the level.
4. Add `AMerrowDiscoveryLandmark` actors where you want story discoveries. Set each one's site type, title, clue text, and page index.
5. Select the forest director and tune its `Merrow | World` properties. Changing a property rebuilds the deterministic layout.
6. Add a player start, lighting, atmosphere director, and a temporary player controller when turning this blockout into a playable test.

The generated scene and landmarks are **greybox placeholders**, not finished realistic art or functional pickup interactions. The next environment-art stage still needs a sculpted Landscape, custom tree/ruin/crystal meshes, material layers, foliage, lighting, post-processing, audio, collision/playtesting, and a proper discovery/save system.

## Build status

The source files are committed, but this project has **not been compiled or tested in Unreal Editor**. GitHub stores the source; it does not compile Unreal projects. A compatible Unreal Engine 5.6 installation and C++ build toolchain are required to verify compilation and run the game.

## Story direction

Ancient Magic once helped shape the first life in Merrow. It fell dormant until something awakened it—and a foreign force infected it. A forbidden book was scattered across the land during the corruption. Its missing pages hold clues to the Entity's weakness and a ritual that may defeat it; every required page must be recovered.

The origin of the Corrupted King and its exact relationship to the Entity remain intentionally undecided while the story develops.

## Source layout

```
Merrow.uproject
Config/
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
      MerrowDiscoveryLandmark.h
      MerrowDiscoveryLandmark.cpp
```
