# Build log

Entries in date order, oldest first. For each session, note what you did, what
went wrong, and what you'd change. The failures are the useful part —
they're what you'll talk about in an interview.

---

## 2026-09-27 — Session 1: first servo test (simulation)

**Goal:** The goal was to just test sample code for a servo on wokwi.com

**What I did:** Added sample servo code to the Arduino UNO simulation, added the servo and its libraries to the simulation

**What went wrong:** Initially forgot to add libraries to simulation

**What I learned:** Do not forget to add necessary libraries

**Next step:** Continue to CAD and learn more about Arduino

**Photos:** [photos/robotic-hand-servo-test.png](../photos/robotic-hand-servo-test.png)

---
## 2026-09-27 — Session 2: designed three finger segments in Fusion

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

**Photos:** [photos/fusion-render-v1-finger.png](../photos/fusion-render-v1-finger.png)

## 2026-09-30 — Session 3: first prints, pin failure, v2 redesign

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

---

## 2026-10-06 — Session 4: tendon routing tests and v2 redesign

**Goal:** Work out why the tendons produced so little flexion, then
redesign the finger around what the tests showed.

### Tendon routing experiments

Strung the printed v1 finger with dental floss, knotted at the tip, and
pulled by hand.

- **Both tendons strung conventionally (flexor bottom, extensor top):**
  very little flexion, roughly 25-30 degrees per joint, and it would not
  go further no matter how much string was pulled through.
- **Routed top-bottom-bottom instead:** significantly more range of
  motion from the same pull.

**What that means:** the limit was never string travel, it was torque.
The crossing route makes the string wrap around the rounded tongue tip
instead of taking a short chord between two channel exits. The tip is a
7.5 mm half-round centred on the pivot, so the wrapped string gets a
7.5 mm moment arm instead of 3.5 mm — more than double the torque for
the same pull.

This is also roughly how real flexor tendons work: they ride over the
joint, held against it by fibrous pulleys, rather than running straight
through the bone.

Several things had to be ruled out first — the base not being anchored,
knots pulling into the channels, friction at square channel exits, and
the joint simply running out of mechanical travel. Isolating one joint
at a time was what made the result readable.

### v2 changes

- **Knuckles** added to the proximal and middle segments to restrict
  hyperextension.
- **Proximal segment** now ends in a ball joint with tendon channels
  through the ball, giving rotation beyond simple flexion/extension
  plus a few degrees of side-to-side wiggle. Channel positions moved
  further from the pivot for a larger moment arm.
- **Middle segment:** channels moved further from the pivot, and the
  paths swept in a cross shape so the same top-to-bottom crossing that
  happens between proximal and middle also happens between middle and
  distal.
- **Distal segment:** channels moved further from the pivot to maximise
  flexion.
- **Connection pins:** replaced the snap-fit barb with two interlocking
  halves (lap joint). The v1 barb was 0.72 mm thick with a slot through
  it, which came out stringy in PETG and snapped on insertion. The v2
  pin has no flexing feature at all — head Ø6 x 1.5, shaft Ø2.88 x 11,
  with the last 4.2 mm cut to a 1.28 mm flat so two pins overlap inside
  the tongue.
- **Socket** designed for the proximal ball joint, with tendon channels
  in the base to carry the tendons from finger to hand. The mouth is a
  slot on one side only: open in the flexion direction (~14 mm, giving
  ~90 degrees), narrow across (8 mm, giving ~6-8 degrees of side-to-side),
  and closed on the other side to prevent hyperextension at this joint.

### Bugs caught by STL analysis

Two defects showed in the exported meshes but not in the CAD, both the
same cause: the ball and neck were modelled as separate bodies that
overlapped the segment rather than being joined to it. Overlapping
bodies render as one solid on screen, so nothing looked wrong, but the
mesh wrote an inside-out shell where they intersected — reported as a
second body with negative volume, plus a phantom void through the centre
of the ball. Fixed with Modify > Combine > Join. The void's diameter
matched the neck's exactly, which is what identified it.

**Lesson:** check body count in the exported mesh, not just the
on-screen model.

### Open questions

- Whether the crossing channel sweep reproduces the wrap effect, or
  whether a dedicated groove around the tongue tip would be better.
- Whether a single flexor tendon curls the fingertip before the base
  joint closes, shrinking the grip aperture.
- Whether the cap screws are strong enough to retain the ball under
  load, since the base bowl is cut at the equator and provides no
  retention on its own.

**Next:** print all six parts (3 segments, 8 lap pins, socket base,
socket cap), assemble, and test the full finger with poly tennis string
and an elastic return before adding a servo.

**Photos:** [photos/full-finger-v2.png](../photos/full-finger-v2.png),
[photos/ball-joint-rom-v2-a.png](../photos/ball-joint-rom-v2-a.png),
[photos/ball-joint-rom-v2-b.png](../photos/ball-joint-rom-v2-b.png)

---

## 2026-10-10 — Session 5: palm v3

**Goal:** Redesign the palm so it can hold a thumb and curve like a real
hand, and round out the wrist for a future splint or wrist controls.

**What I did:**

- **Arch:** curved the palm across its width (15° total), flat near the
  wrist and fully curved by the knuckles, with a smooth curve instead of
  a sharp fold. Finger slots roll with it: index −7.5°, middle 0°,
  ring 7.5°, pinky 15°.
- **Wrist:** rounded oval (60 × 29 mm) instead of a rectangle.
- **Wrist cap:** new round cap with a D-shaped flat so it only fits one
  way. 12 tendon holes in 6 columns (thumb, index, middle, ring, pinky,
  plus one spare) × 2 rows (palm side = flexors). No labels, since small
  printed text came out unreadable last time.
- **Tendon paths:** 15 × 15 mm tunnels from each finger slot that merge
  into one funnel chamber leading to the wrist cap.
- **Thumb:** housing for an MG90S micro servo in the thenar area (base
  of the thumb), with a hinge lug, a thumb tendon channel, and a channel
  for the servo wires. The thumb will swing across the palm on the servo
  and flex on its own tendon.

**What went wrong (caught before printing):**

1. The servo's top and mounting tabs collided with palm material, and
   the screw slot came out as a sealed void inside the part. Fixed with
   clearance cuts.
2. Several walls came out too thin: the funnel was too tall at first,
   and the thumb tendon channel's floor was too thin. Fixed by reshaping
   the funnel and raising the channel.
3. Thin wedges where the tunnels split were left as-is, since they're
   small and non-structural.

**What I learned:**

- Fit-check every part that goes into a pocket (servo body, tabs,
  screws, wires) against the walls, not just the main body.
- A rounded wrist costs almost nothing now and keeps options open for
  wrist rotation and a splint later.

**Next step:** Print the palm with one finger and check that the sockets
and cap seat properly.

**Photos:** [photos/palm-v3-preview.png](../photos/palm-v3-preview.png)

---

## 2026-10-14 — Session 6: knuckle joint v5 (tendons through the ball joint)

**Goal:** Get both tendons through the ball-and-socket knuckle and reach
a full 90° of flexion, using 17-gauge (1.25 mm) poly tennis string.

**What went wrong with v2:**

1. **No room for the string.** The ball fit the socket with only
   ~0.15 mm of clearance. The tendon channels went straight through the
   ball and came out behind the pivot, inside the bowl, but the socket
   holes were 1.75 mm further out (±6.75 vs ±5 mm). The string had to
   squeeze between the ball and the bowl.
2. **Uncrossed strings would have worked backwards.** Because the
   channels came out behind the pivot, pulling the palm-side string
   would have *straightened* the finger. That's why crossing seemed
   necessary.
3. **The base stopped the finger at ~60°.** Only the cap had a slot, so
   the neck hit the base rim before 90°.
4. **The cap blocked the back-side string.** Its opening is 4 mm from
   center and the string runs at 5 mm.

**Options considered:**

- **Cross both strings under the ball in grooves.** This gives a
  constant ~4.9 mm moment arm, but two strings crossing need separate
  side-by-side grooves, which puts them off-center. The neck is round,
  so nothing stops the finger rolling: off-center strings would twist
  it. The crossed extensor would also need a notch in the base of the
  neck near full bend. And both strings make a ~140° U-turn into their
  holes, which is bad for stiff tennis string.
- **Uncrossed, centered (chosen).**

**v5 changes:**

- **Proximal segments (all four fingers):** channels now stop at the
  body instead of tunneling through the ball. One 2.0 mm groove wraps
  around the back of the ball (±130°), on the center line.
- **Socket base:** 8.4 mm slot on both sides, cut down to 6 mm, so the
  finger reaches 90° and the slot floor is the stop (~92°). Two Ø2.2
  holes on the center line, 5 mm toward the palm and toward the back,
  with chamfered edges. A small channel in the slot floor keeps the
  string under the neck at full bend. Same either way round.
- **Socket cap:** added a 2.6 mm slot on the back side for the extensor.
- **Middle segments v3:** more spacing at the forks (my change).

**Checked before printing** (all three parts assembled, 1.25 mm
string):

- No collisions from straight to 93°.
- Both string paths clear at every angle.
- The palm-side string bends the finger; pulling ~9.3 mm takes it from
  straight to 90°, with a 5.5–6.5 mm moment arm.
- The back-side string pays out ~7.9 mm over the same bend (~5 mm
  arm). If one servo drives both, the extensor goes ~1.4 mm slack by
  full bend, so it needs a small spring.

**What I learned:**

- Crossing isn't what makes a tendon flex a joint. What matters is
  which side of the pivot the string leaves the segment on, and staying
  off-center from the pivot the whole way.
- Check clearances with every part assembled, including the cap. Each
  part looked fine on its own.
- On a ball joint, keep tendons on the center line. Nothing else resists
  twisting.

**Open question:**

- Session 4 routed the flexor top-bottom-bottom, so it sits in the
  *top* channel of the proximal. The v5 knuckle needs the flexor in the
  proximal's *palm-side* channel. Test which routing flexes all three
  joints on the test finger.

**Next step:** Print the palm, one middle finger (v5 proximal + v3
middle + distal + pins), 2 socket bases and 1 cap. Check:

1. Socket fits the palm and the cap pegs snap together
2. The ball groove printed clean, with no support stuck in it
3. Tennis string passes through the channels (drill with 2 mm if tight)
4. Finger reaches 90° by hand with strings in
5. Flexor pull bends it smoothly; extensor pull straightens it

**Photos:**
[photos/joint-v5-section.png](../photos/joint-v5-section.png),
[photos/joint-v5-why-flexor-flexes.png](../photos/joint-v5-why-flexor-flexes.png)

---

### Template to copy for each session

```
## YYYY-MM-DD — Session N: title

**Goal:**
**What I did:**
**What went wrong:**
**What I learned:**
**Next step:**
```
