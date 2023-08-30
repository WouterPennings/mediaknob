# Instructions

Here you will find the component list, schematics, and instructions to build the media knob.

## Components

- Arduino Pro Micro 5V ([Sparkfun](https://www.sparkfun.com/products/12640))
  - Make sure you buy a Pro Micro with identical dimensions to the Sparkfun one
- EC11 Rotary encoder ([Aliexpress](https://nl.aliexpress.com/item/1005002802225957.html?spm=a2g0o.productlist.main.73.1a476867OZREEx&algo_pvid=b6bf1163-fa66-4662-8d6a-866a64e69d97&algo_exp_id=b6bf1163-fa66-4662-8d6a-866a64e69d97-36&pdp_npi=4%40dis%21EUR%210.63%210.51%21%21%210.67%21%21%40211b617a16933239714535859e7a21%2112000022266485904%21sea%21NL%210%21A&curPageLogUid=IVOv2xvNuyEq))
- All 3D printed parts STL files can be found in [3d](/3d)
- Some electrical wire or five jumper wires
- M3 nuts + M3*20 bolts (M3*10 bolts is also fine, but not preferred)
- Micro USB cable

### Equipment

- 3D printer, or use a 3D printing service.
- Soldering iron
- Solder
- Flux, not necessary, but could help
- Hex driver

## Electrical Schematic

The pins in this schematic are connected to `D2`, `D4`, and `D6`. You could use other pins, even the analog ones, however you would have to refactor the code accordingly.

<div>
  <img src="/images/electrical%20schematic.png" width="45%">
  <img src="images/soldering.jpg" width="45%">
</div>

## Assembly Guide

1. 3D print all the components.
   - **Tip**: Print with a higher infill percentage if possible, it makes the print heavier and therefore a more premium feeling.
2. Melt one M3 nut into each pillar of the [chassis](3d/chassis.stl) using a hot soldering iron.
3. Screw the rotary encoder into the [main board](3d/main_board.stl), and insert the Arduino Pro Micro into its slot.
4. Solder the five rotary encoder pins to the correct pins of the Arduino. Follow the schematic given earlier.
   - Soldering to a rotary encoder can sometimes be a bit tedious. If you are a beginner or otherwise need help, follow [this guide on Youtube](https://youtu.be/2pfKgR3CWr4?si=yPZcE0ex2ldTHdDo).
5. Upload the firmware and test all functionality of the knob. This way you know if there is something wrong before tightening the bolt and attaching the button.
   - Steps on how to upload the firmware are given at the bottom of this page.
7. Bolt the [chassis](3d/chassis.stl) to the [main board](3d/main_board.stl) and attach the [button](3d/button.stl) to the shank of the rotary encoder.

### Upload Firmware

First make sure that you have solderd your knob completely.

1. Clone this repository: `git clone https://github.com/WouterPennings/mediaknob.git`
2. Install [Arduino IDE 2.X](https://www.arduino.cc/en/software)
3. Install the `Button2` and `HID-Project` on the left side of the screen in the `Library` tab
4. Plug your Arduino Pro Micro into your computer using the Micro USB cable, select the correct COM port in the Arduino IDE.
5. Press the `Upload` button and wait until the code is compiled and uploaded to your Arduino

> **Tip**: Use the serial monitor to debug if your knob show unexpected behaviour