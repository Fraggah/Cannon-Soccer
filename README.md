# Cannon Soccer

<img width="1193" height="790" alt="image" src="https://github.com/user-attachments/assets/67a3edd2-b5d0-4cfa-ac46-fda22d76648f" />

<img width="1198" height="800" alt="image" src="https://github.com/user-attachments/assets/1173fefe-eb9d-4ad0-bfed-91f23e8df8fe" />

**Genre:** Physics Puzzle / Skill  
**Tech:** C++17, SFML (render/input/audio), Box2D (physics)  
**Platform:** PC (Windows/Linux)

Cannon Soccer is a physics‑driven arcade puzzle where you fire ragdolls from a cannon to hit balls into the goal. Everything non‑engine is coded from scratch: sprite animation system, particle system, screen transitions, interactive music, and a lightweight game state framework.

---

## 🎮 Core Systems & Features

- **Ragdoll Physics (Box2D):**  
  - Multi‑body rigs (head/torso/limbs) connected via `b2RevoluteJoint` with angle limits and motor impulses.  
  - Tuned mass/inertia and damping for believable yet playful motion.  
  - Collision filtering to avoid self‑collision artifacts (layer masks & categories).

- **Ball‑to‑Goal Gameplay:**  
  - Balls with restitution/linear damping and optional CCD for high‑speed impacts.  
  - Goal line sensors using `b2Fixture` with `isSensor = true` and contact callbacks for scoring.

- **Cannon Mechanics:**  
  - Adjustable angle/power with trajectory preview (analytical estimate blended with sampled impulses).  
  - Cooldown, limited ammo, and wind/random field toggles for stage variety.

- **From‑Scratch 2D Animation System:**  
  - Keyframe‑based sprite animator (per‑track blend, playback speed, ping‑pong, events).  
  - Ragdoll “puppet” overlay tying animation states to physics poses (pose blending with constraints).

- **Custom Particle System:**  
  - CPU‑driven emitters (bursts/continuous), lifetime curves (size, velocity, rotation, alpha).  
  - Batched rendering with SFML vertex arrays to minimize draw calls (no per‑sprite overhead).

- **Screen Transitions & UI:**  
  - Fade/wipe/iris transitions (time‑based easing).  
  - Simple UI kit (buttons, sliders) with focus/tab navigation and gamepad mapping.

- **Interactive Music & SFX:**  
  - Layered tracks that cross‑fade based on gameplay intensity (cannon charge, slow‑mo, goal).  
  - Parameter‑driven mixer (C++), one‑shot SFX with pitch variation for variety.

- **Game States & Tools:**  
  - Finite State Machine: `Boot → Menu → Level → Results` with stack‑based overlays (Pause).  
  - In‑game dev console (toggle), physics debug draw, contact spam limiter, profiler overlay (FPS, bodies, contacts).

---

## 🛠 Technical Challenges & Solutions

- **Ragdoll instability at high impulses**  
  **Solution:** Clamped impulses, joint torque limits, and slightly increased solver iterations only for ragdoll joints to keep stacks stable.

- **Ball tunneling on powerful shots**  
  **Solution:** Enabled Box2D bullet mode on balls for CCD; reduced time step when velocity exceeds threshold (`fixed Δt` with sub‑stepping cap).

- **Sprite/physics desync**  
  **Solution:** Fixed‑timestep physics (`60 Hz`) decoupled from variable render; interpolation of transforms on the render thread.

- **Contact callback storms (score sensors)**  
  **Solution:** Debounce window and one‑shot scoring flag per ball; contact queue processed post‑step to avoid re‑entrancy.

- **Particle overdraw & CPU spikes**  
  **Solution:** Emitter pooling + per‑frame batch rebuild only for live particles; optional LOD by distance and cap on max quads.

---
