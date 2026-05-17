# 🐄 Farm Frenzy

A C++ farm management game built using the CMUgraphics library and SFML audio. Buy animals, collect produce, fend off wolves, and grow your fortune across 5 increasingly challenging levels.

---

## 📖 About

Farm Frenzy is a Windows desktop game developed as a university project. Players manage a farm by purchasing chickens and cows, collecting the eggs and milk they produce, selling goods through the warehouse, and defending their animals against wolves that roam the playing field.

---

## 🎮 Gameplay

- **Buy animals** — use the budget bar to purchase chickens and cows, which are placed on the farm.
- **Collect produce** — click eggs and milk that appear on the ground to send them to the warehouse.
- **Sell goods** — click the warehouse icon to open an inventory popup where you can sell eggs ($200 each), milk ($400 each), or everything at once.
- **Deal with wolves** — wolves spawn and roam the field. Click a wolf 5 times to eliminate it, drag it into the cage to trap it, or buy the cage upgrade ($8,000) to contain wolves permanently.
- **Level up** — reach money thresholds to advance through 5 levels. Higher levels spawn faster and more numerous wolves.

### Level Progression

| Level | Budget Threshold | Goal    | Timer |
|-------|-----------------|---------|-------|
| 1     | Starting         | $10,000 | 90s   |
| 2     | $10,000          | $15,000 | 90s   |
| 3     | $15,000          | $20,000 | 60s   |
| 4     | $20,000          | $50,000 | 30s   |
| 5     | $50,000          | —       | 20s   |

---

## 🖥️ Controls

| Action | Input |
|--------|-------|
| Buy animal / Use toolbar | Left click |
| Collect egg or milk | Left click on item |
| Attack wolf | Left click wolf (×5 to eliminate) |
| Drag wolf to cage | Hold left click, drag to cage area |
| Open warehouse | Left click warehouse icon |
| Pause / Resume | Toolbar buttons |
| Save / Load game | Toolbar buttons |
| Restart | Toolbar button |

---

## 🏗️ Project Structure

```
meowerr-farmfrenzy/
├── main.cpp                  # Entry point
├── Core/
│   ├── Game.cpp / Game.h     # Main game loop, event handling, level logic
│   ├── GameObject.cpp / .h   # Base class for game objects
│   └── Drawable.cpp / .h     # Base class for anything drawn on screen
├── Entities/
│   └── Animal.cpp / .h       # Base animal class with movement and production
├── UI/
│   ├── Toolbar.cpp / .h      # Top toolbar (Restart, Pause, Resume, Save, Load, Exit)
│   └── BudgetBar.cpp / .h    # Secondary bar for buying animals
├── Config/
│   └── GameConfig.h          # Window size, colors, and layout constants
├── Grass.cpp / .h            # Grass/field rendering
├── Warehouse.cpp / .h        # Warehouse inventory and selling logic
├── Wolf.cpp / .h             # Wolf enemy with movement, drag-and-drop, and cage logic
├── SoundEffects.cpp / .h     # SFML-based sound effects
├── CMUgraphicsLib/           # Graphics library (CMU, Windows GDI-based)
│   └── jpeg/                 # JPEG decoding support
└── packages/                 # NuGet packages (SFML audio & system)
```

---

## ⚙️ Requirements

- **OS:** Windows (Win32)
- **IDE:** Visual Studio (solution file included: `graphics_prj.sln`)
- **Audio:** SFML 2.4.2 (included via NuGet packages)
- **Graphics:** CMUgraphics library (included in `CMUgraphicsLib/`)

---

## 🚀 Building & Running

1. Open `graphics_prj.sln` in Visual Studio.
2. Restore NuGet packages if prompted (SFML audio/system).
3. Build in **Debug** or **Release** configuration (Win32).
4. Run the executable. Make sure the `images/` folder and `.ogg` / `.wav` sound files are in the same directory as the binary.

> **Note:** The project targets Win32 (x86). Ensure you select the correct platform in Visual Studio before building.

---

## 🔊 Sound Effects

Sound effects are played using SFML for the following events:

- Chick / Cow / Cat / Wolf sounds
- Grass interaction
- UI clicks
- Item drop
- Level up

---

## 💾 Save & Load

The game supports saving and loading progress via the toolbar. Game state is persisted to `savegame.txt`, and high scores are recorded in `FarmScores.txt`.

---

## 👥 Authors

Developed at Zewail City of Science and Technology.

- **Abdullah Mustafa** — s-abdullah.alshazly@zewailcity.edu.eg
- **Youssef Saqib** — s-youssef.saqib@zewailcity.edu.eg
- **Omar Tareq** — s-omar.hassounah@zewailcity.edu.eg
- **Abdelmalek Mohamed** — s-abdelmalek.abdalla@zewailcity.edu.eg

---

## 📚 Third-Party Libraries

- **CMUgraphics** — Windows GDI-based 2D graphics library from Carnegie Mellon University
- **libjpeg** — JPEG image decoding (bundled within CMUgraphicsLib)
- **SFML 2.4.2** — Audio playback (sfml-audio, sfml-system)