# cub3D — Raycaster with MiniLibX

![C](https://img.shields.io/badge/language-C-blue)
![42 School](https://img.shields.io/badge/school-42-black)

> Built as part of the 42 curriculum by **loasaad** and **latabagl**.

A small first-person 3D engine written in C, inspired by Wolfenstein 3D. The engine renders a real-time 3D environment from a 2D map using the MiniLibX graphics library.

---

## Description

cub3D casts rays from the player's viewpoint to detect walls, computes their projected height on screen, and maps textures onto each vertical slice — producing a first-person view complete with textured walls and basic shading.

The project covers core computer graphics concepts: raycasting, texture mapping, perspective projection, and image buffer rendering, while reinforcing skills in C programming, memory management, and mathematical computation.

---

## Getting started

### Build

```bash
make           # compile cub3D
make bonus     # compile with bonus features
```

### Run

```bash
./cub3D maps/map.cub
```

The `.cub` file defines the map layout, texture paths, and color settings.

### Clean

```bash
make clean     # remove object files
make fclean    # remove object files and binary
make re        # fclean + recompile
```

---

## Controls

| Key | Action |
|-----|--------|
| `W` `A` `S` `D` | Move forward / left / backward / right |
| `←` `→` | Rotate camera |
| `ESC` | Exit |

**Bonus controls:**

| Key | Action |
|-----|--------|
| `E` | Open / close a door |
| `Space` | Shoot |

---

## Rendering pipeline

1. **Raycasting** — rays are cast from the player's position across the field of view to find the nearest wall in the grid.
2. **Wall projection** — ray distance is used to compute the projected height of each wall slice via perspective projection.
3. **Texture mapping** — the correct texture (N/S/E/W) is selected and sampled at the right pixel coordinates.
4. **Shading** — a basic effect differentiates wall orientations to simulate lighting.
5. **Rendering** — colored pixels are written to the image buffer and displayed via MiniLibX.

---

## Map file format (.cub)

### Textures

NO path/to/north_texture.xpm
SO path/to/south_texture.xpm
WE path/to/west_texture.xpm
EA path/to/east_texture.xpm

### Floor and ceiling colors
F 220,100,0
C 225,30,0

### Map layout

| Character | Meaning |
|-----------|---------|
| `1` | Wall |
| `0` | Empty space |
| `N` `S` `E` `W` | Player start position and orientation |
| ` ` | Unused space |

```
111111
100001
10N001
100001
111111
```

> The map must be fully enclosed by walls.

### Bonus map characters

| Character | Meaning |
|-----------|---------|
| `D` | Door |
| `T` | Teleporter (max 2 per map) |
| `F` | Fruit |
| `.` | Food |
| `G` | Ghost enemy |

---

## Resources

- [lodev.org — Raycasting tutorial](https://lodev.org/cgtutor/raycasting.html)
- [42docs — MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [YouTube — Raycasting explained](https://www.youtube.com/watch?v=gYRrGTC7GtA)

---

## Use of AI

AI was used to help refine code comments for clarity, answer theory questions, assist with refactoring, and think through design decisions.