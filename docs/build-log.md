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

## 2026-09-30 — Session 2: first prints, pin failure, v2 redesign

**Goal:** Print the three finger segments and the snap-fit pivot pins,
assemble the finger, and check fit and range of motion.

**What I did:**

- Printed all three segments in PLA at the Invention Studio (FDM,
  Bambu Lab X1E), oriented on a side face so the pivot holes printed as
  vertical circles with no supports.
- Printed the connection pins in PETG. Removed supports and brim with
  flush cutters, filed the tongue and fork faces flush.
- Assembled the finger with pin fragments, confirmed both joints rotate
  ~90 degrees in each direction.
- Redesigned the pin as a two-part lap joint (v2) and widened nothing
  else.
- Added a knuckle shell over the joints and a tapered lip that acts as
  a hyperextension stop.

**What went wrong:**

1. **PETG pins came out stringy**, specifically on the slotted barb at
   the tip. Printing them vertically did not help. The barb halves were
   0.72 mm thick with a slot between them — too fine a feature for FDM
   in a material that strings as much as PETG.

2. **The pins snapped during insertion** and would not have fitted even
   if the barb had compressed cleanly. The barb was Ø4.05 going into a
   3.2 mm hole, so each half had to deflect ~0.43 mm over an 11 mm
   cantilever, in a brittle printed part.

3. **Discovered the fix by accident:** after the pins broke in half, the
   plain shaft fragments fitted the holes perfectly. Pushed one fragment
   into each side of a joint and the finger assembled and moved well.
   The barb was the fragile part and it turned out to be unnecessary.

**What I learned:**

- Feature size has to be matched to the process, not just to the design
  intent. A snap fit asks a brittle material to flex, which is the one
  thing it is bad at.
- Material choice drives stringing far more than print orientation does.
- A simpler mechanism that cannot fail beats a clever one that can. The
  two-stub pin has no flexing feature at all.
- Choosing a different manufacturing process per part (SLA for fine
  features, FDM for the bulk parts) is a legitimate design decision.

**v2 changes:**

- **Pin:** two-part lap joint. Head Ø6 x 1.5, shaft Ø2.88 x 11 mm,
  with the last ~4.2 mm cut down to a 1.28 mm flat so two pins overlap
  inside the tongue. Mated thickness 2.56 mm inside a 2.88 mm envelope.
  Combined reach 17.8 mm across a 17 mm joint stack, leaving ~0.8 mm
  axial play. No slot, no barb, nothing to snap.
- **Segments:** knuckle shell added over the joints; tapered lip added
  as a hyperextension stop so the finger stops at straight.

**Tendon routing decided:**

- Flexor runs through the bottom channel of all three segments, anchored
  at the tip. Extensor runs through the top channel of all three.
- The direction a tendon turns a joint depends on which side of the
  pivot it passes. Below the pivot closes the joint, above it opens it.
  A line through the pivot centre produces no torque at all.
- Flexion limited to ~90 degrees. Beyond that the tendon line crosses
  the pivot axis and pulling would start to extend the joint instead
  (over-centre).
- Planned: connect the two channels with a cross-hole near the distal
  tip so one continuous loop serves as both flexor and extensor, with
  no knot to slip.

**Open questions:**

- Whether the tendon channels should move further from the pivot
  (4 mm -> 2.5 mm from the bottom face) for a larger moment arm.
- Whether a single flexor will curl the fingertip before the base joint
  closes, which would shrink the grip aperture.
- Whether the lap pins migrate outward in use. Fallback is a dab of glue
  in the fork prong holes only, leaving the tongue free to rotate.

**Next step:** reprint segments and 8 lap pins. Thread a tendon and
confirm flexion direction by hand before motorising.

**Photos:** docs/photos/

### Template to copy for each session

```
## YYYY-MM-DD — Session N: title

**Goal:**
**What I did:**
**What went wrong:**
**What I learned:**
**Next step:**
```
