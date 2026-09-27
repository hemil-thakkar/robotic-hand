# robotic-hand
# Tendon-driven robotic hand

Building a tendon-driven robotic hand as a step toward prosthetics and
wearable robotics research. Based on the open-source
[InMoov](https://inmoov.fr) hand, with my own modifications.

Biomedical engineering, Georgia Tech.

## Goals

- [ ] Print and assemble a single working finger
- [ ] Drive the finger with a servo and Arduino
- [ ] Build the full hand and forearm
- [ ] Design my own parts (mount, electrode holder, modified joint)
- [ ] Compare my finger design against the original for grip and range of motion
- [ ] Control the hand with an EMG (muscle) signal

## Status

Stage 0: printing the first finger.

## Repo layout

| Folder | Contents |
|---|---|
| `cad/` | My Fusion designs and exported STL files |
| `code/` | Arduino sketches and analysis scripts |
| `docs/` | Build log, photos, test results |
| `data/` | Measurements from tests |

## Built with

- 3D printing at the Georgia Tech Invention Studio
- Autodesk Fusion for CAD
- Arduino for servo control

## Credit

Mechanical design based on the InMoov open-source humanoid robot by
Gael Langevin, licensed CC-BY-NC. My own parts and code are in `cad/`
and `code/` and noted as mine in the build log.
