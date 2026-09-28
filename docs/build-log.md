# Build log

Newest entries at the top. For each session, note what you did, what
went wrong, and what you'd change. The failures are the useful part —
they're what you'll talk about in an interview.

---

## 2026-09-27 — Session 1: first servo test

**Goal:** The goal was to just test sample code for a servo on wokwi.com

**What I did:** Added code from Claude to the Arduino UNO simulation, added servo into the simulation and its libraries

**What went wrong:** Initially forgot to add libraries to simulation

**What I learned:** Do not forget to add necessary libraries

**Next step:** Continue to CAD and learn more about Arduino

**Photos:** [robotic-hand/photos/robotic-hand-servo-test](url)

---
## 2026-09-27 — Session 1: designed three finger segments in Fusion

**Goal:** Learn CAD by designing a tendon-driven finger from scratch
before looking at how InMoov solved it.

**What I did:** Modeled three segments (proximal, middle, distal) as
separate components in one Fusion file. Each has a fork at one end, a
tongue at the other, pivot holes through both, and a 2 mm tendon
channel running the full length below the pivots. Distal segment has
no fork and gets a counterbore at the tip so the tendon knot sits
recessed. Assembled with revolute joints and set joint limits.
Exported STLs.

**What went wrong:**

1. The 3-point arc bulged 7.5 mm past the rectangle, making the part
   47.5 mm instead of 40. Fixed by shortening the rectangle to 32.5 so
   rectangle + arc = intended length.

2. Adding a fillet to the tongue tip broke the pivot hole, because the
   circle was under-constrained and moved when the geometry changed.
   Fixed by making the hole's center coincident with the fillet arc's
   center — which is also the correct design, since the pivot should
   sit at the center of rotation.

3. Copying the segment and shortening it made the fork disappear
   entirely. The fork sketch was drawn at fixed coordinates that
   covered the rounded end at 40 mm, but landed off the part at 25 mm.

4. On the shorter segment, the fork and tongue nearly collided. Feature
   sizes that fit a 40 mm segment don't fit a 25 mm one.

**What I learned:**

- Geometry dimensioned from fixed coordinates doesn't move when the
  part changes; geometry constrained to projected features does.
  Rebuilt the sketches using Project so the fork and holes reference
  the arc instead of the origin.
- Fully constrained sketches (black geometry, padlock in browser)
  aren't cosmetic — they're what makes a design survive edits.
- Feature dimensions need to scale with the part, not stay fixed.
  A parameter like tongueLen = segLength * 0.25 would handle this.
- Fusion's new intent-driven design dialog: Hybrid mode is the
  classic everything-in-one-file workflow.
- Printer nozzles are 0.4 mm, so the minimum reliable feature is
  about 0.8–1 mm. Nothing in this design is close to that.

**Design decisions:**

- Segment lengths: 40 / 25 / 20 mm, adult index finger
- Cross section: 18 mm wide × 15 mm thick
- Tongue 6 mm thick into a 6.4 mm fork slot (0.2 mm clearance per side
  — may need widening once printed)
- 3.2 mm pivot holes for M3 bolts with nyloc nuts
- 7.5 mm tongue tip fillet = true half-round, centered on the pivot

**Next step:** Print one segment at the Invention Studio to check fit
and tolerances before printing all three. Source 2× M3 bolts and nyloc
nuts (~22–25 mm long) from Robo 101, WEAR, or the Hive.

**Photos:** [photos/robotic-hand-servo-test.png](url)


### Template to copy for each session

```
## YYYY-MM-DD — Session N: title

**Goal:**
**What I did:**
**What went wrong:**
**What I learned:**
**Next step:**
```
