# openGL-aquarium

This project is an OpenGL-based simulation of an aquarium for course Computer graphics. 

---

## Controls & Interaction

### **3D Simulation Controls**
| Action | **Goldfish** | **Nemo / Clownfish** |
| :--- | :--- | :--- |
| **Horizontal (X/Z axis)** | `W`, `A`, `S`, `D` | `Up`, `Down`, `Left`, `Right` |
| **Vertical (Up/Down)** | `Q` (Up) / `E` (Down) | `K` (Up) / `L` (Down) |
| **Bubbles** | `1` | `2` |

* **Treasure Chest:** Press `G` to open/close (activates internal golden light).
* **Feeding:** Press `ENTER` to drop food particles.
* **Rendering Toggles:** `T` (Depth Test), `C` (Face Culling).

---

### **2D Simulation Controls**
| Action | **Goldfish** | **Nemo / Clownfish** |
| :--- | :--- | :--- |
| **Movement** | `W`, `A`, `S`, `D` | `Up`, `Down`, `Left`, `Right` |
| **Bubbles** | `Z` | `K` |

* **Treasure Chest:** Press `C` to open/close.
* **Feeding:** Press `ENTER` to drop food.

---

### **2D Simulation**
* **Environment:** Rectangular aquarium with a 10px black border and a 20% transparent water overlay.
* **Assets:** Sand-textured floor and animated seaweed stalks.
* **Mechanics:** Fish textures mirror horizontally when changing direction.
* **Cursor:** Custom anchor-shaped cursor.
* **Growth Mechanic:** Fishes increase in thickness each time they eat food.

### **3D Simulation**
* **Advanced Rendering:** Uses custom `.obj` models for fish, seaweed, food, and the chest.
* **Terrain:** The sand is rendered as an irregular polygon mesh for a natural look.
* **Lighting System:**
    * **Global Light:** A soft pink ambient and diffuse light source illuminates the scene.
    * **Point Light:** A dynamic golden light emerges from the treasure chest upon opening.
* **Transparency:** Alpha blending is applied to glass walls, air bubbles, and water surfaces.
* **Growth Mechanic:** Fishes increase in thickness each time they eat food.
  
---

* **Frame Limiter:** Locked at **75 FPS** for smooth animation and physics consistency.
* **Collision Detection:** 
    * Positional boundaries to keep fish inside the aquarium walls.
    * Collision logic to prevent fish from passing through the 3D chest model.
* **State Management:** Toggleable OpenGL states (`GL_DEPTH_TEST`, `GL_CULL_FACE`) to demonstrate optimization techniques.

---

