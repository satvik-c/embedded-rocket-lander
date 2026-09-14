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
The firmware operates completely bare-metal without an RTOS, utilizing hardware interrupts to manage concurrent tasks:
- **Audio Engine:** Background audio playback is seamlessly handled by the `SysTick_Handler` routine.
- **Game Loop:** A dedicated hardware timer (`TIMG12`) triggers semaphores at a precise frequency, pacing the physics engine, rendering, and collision detection to guarantee a deterministic frame rate.

### Fixed-Point Physics Engine
Because the Cortex-M0+ lacks a hardware floating-point unit, utilizing standard floating-point math would introduce severe software overhead. Instead, the physics engine relies entirely on **pre-computed lookup tables**. These tables perform all trigonometric math required for thrust vectoring, trajectory projection, and 32-directional sprite rendering with minimal CPU cycles.

### Memory & Resource Management
To strictly conserve the microcontroller's limited SRAM, all graphical pixel-art assets and PCM audio waveforms are stored as constant arrays directly in Flash ROM. Hardware peripherals are controlled efficiently through direct memory-mapped register configuration.
