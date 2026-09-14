<div align="center">
  <h1>Rocket Lander</h1>
  <p><strong>A bare-metal lunar lander simulation game for the TI MSPM0G3507.</strong></p>
</div>

<br>

Developed as the capstone project for UT Austin's ECE 319H (Introduction to Embedded Systems), Rocket Lander challenges players to pilot a spacecraft to a safe lunar landing by managing thrust vectors and velocity.

**Authors:** Satvik Chawla & Shane Nguyen

---

## Game Features
- **Dynamic Physics:** Continuous thrust and trajectory management.
- **Configurable Rounds:** Tracks successful landings versus crashes across multiple sessions.
- **Dynamic Localization:** String-table lookup system allows for real-time language swapping without hardcoded string literals.

## Hardware Architecture
- **Core:** Texas Instruments MSPM0G3507 (80MHz ARM Cortex-M0+)
- **Display:** ST7735 1.8" Color TFT LCD (driven via hardware SPI)
- **Controls:** 
  - **Slide Potentiometer:** 12-bit hardware ADC for fluid steering input.
  - **Push Buttons:** Direct GPIO polling with software edge-detection and debouncing.
- **Audio:** Digital-to-Analog Converter (DAC) outputting PCM sound effects to an external speaker.

## Technical Implementation

### Interrupt-Driven Concurrency
- **Bare-Metal Architecture:** Firmware operates completely bare-metal without an RTOS, utilizing hardware interrupts to manage concurrent tasks.
- **Background Audio:** The `SysTick_Handler` routine seamlessly manages continuous PCM audio playback independent of game logic.
- **Deterministic Game Loop:** A dedicated hardware timer (`TIMG12`) triggers semaphores at a precise frequency to pace the physics engine, rendering, and collision detection.

### Fixed-Point Physics Engine
- **No FPU Overhead:** The Cortex-M0+ lacks a hardware floating-point unit; all floating-point math is bypassed to avoid severe software execution overhead.
- **Pre-Computed Math:** The physics engine relies entirely on pre-computed lookup tables for trigonometric calculations.
- **Complex Rendering:** Tables efficiently handle thrust vectoring, trajectory projection, and 32-directional sprite rendering using minimal CPU cycles.

### Memory & Resource Management
- **SRAM Conservation:** Strictly conserves the microcontroller's limited SRAM by utilizing Flash memory for static data.
- **Constant Arrays:** All graphical pixel-art assets and PCM audio waveforms are stored as constant arrays directly in Flash ROM.
- **Direct Register Access:** Hardware peripherals are controlled efficiently through direct memory-mapped register configuration rather than heavy abstraction layers.
