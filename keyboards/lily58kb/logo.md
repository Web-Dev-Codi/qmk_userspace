# Creating Custom OLED Logos for Lily58 Keyboard

This guide provides step-by-step instructions for creating and implementing custom logos on the OLED displays of your Lily58 keyboard.

## Table of Contents
1. [Understanding OLED Display Dimensions](#understanding-oled-display-dimensions)
2. [Creating an Image in GIMP](#creating-an-image-in-gimp)
3. [Converting the Image to C Array](#converting-the-image-to-c-array)
4. [Implementing the Logo in QMK](#implementing-the-logo-in-qmk)
5. [Compiling and Flashing](#compiling-and-flashing)
6. [Troubleshooting](#troubleshooting)

## Understanding OLED Display Dimensions

The Lily58 keyboard typically uses 128x32 pixel OLED displays. When creating custom logos, you need to ensure your image matches these dimensions.

## Creating an Image in GIMP

### Step 1: Create a New Image
1. Open GIMP
2. Go to **File > New**
3. In the "Create a New Image" dialog:
   - Set Width to **128 pixels**
   - Set Height to **32 pixels**
   - Under "Advanced Options," set the "Fill with" option to "Transparency"
   - Click "Create"

### Step 2: Set Up the Image for OLED Display
1. Go to **Image > Mode > Grayscale** (since OLED displays are monochrome)
2. Go to **Image > Mode > Indexed** to convert to a 1-bit image
   - Select "Use black and white (1-bit) palette"
   - Click "Convert"

### Step 3: Create Your Design
1. Use the Text tool to add text (e.g., "Lily58KB")
   - Select a font that's clear at small sizes
   - Set the text color to white (for black background OLED) or black (for white background OLED)
2. Position the text where you want it on the display
3. You can add additional design elements as needed

### Step 4: Export the Image
1. Go to **File > Export As**
2. Save the file as a PNG
3. Name it something like "lily58kb_logo.png"
4. Click "Export"
5. In the PNG export dialog, just click "Export" with the default settings

## Converting the Image to C Array

### Step 1: Use image2cpp
1. Go to [image2cpp](https://javl.github.io/image2cpp/)
2. Upload your PNG file
3. Configure the settings:
   - Set "Canvas Size" to match your image (128x32)
   - Set "Background color" to match your design (black or white)
   - Choose "Code output format" as "Arduino code (single array)"
   - Set "Identifier" to "lily58kb_logo"
   - Check "Draw mode" as "Horizontal - 1 bit per pixel"
4. Click "Generate code" to get your C array
5. Copy the generated code

## Implementing the Logo in QMK

### Step 1: Add the Logo to display_oled.c
1. Open `/keyboards/lily58kb/common/display_oled.c`
2. Create a new function to display your custom logo:

```c
static void render_custom_logo(void) {
    static const char PROGMEM custom_logo[] = {
        // Paste your generated C array here
        // It will look something like:
        // 0x00, 0x00, 0x00, ... many more bytes
    };
    oled_write_raw_P(custom_logo, sizeof(custom_logo));
}
```

### Step 2: Modify the Slave OLED Initialization
Update the `oled_reinit_slave()` function to use your custom logo:

```c
void oled_reinit_slave(void) {
    oled_init(OLED_ROTATION_270);
    oled_clear();
    oled_set_cursor(0, 0);
    render_custom_logo();  // Use your new function
}
```

## Compiling and Flashing

1. Save all changes
2. Compile the firmware:
   ```
   qmk compile -kb lily58kb/lily58/rev1 -km default
   ```
3. Flash the firmware to both halves of your keyboard:
   - Put the master half into bootloader mode and flash it
   - Then put the slave half into bootloader mode and flash it

## Troubleshooting

### Image Doesn't Display Correctly
- Try adjusting the threshold in image2cpp
- Experiment with different OLED rotations (0, 90, 180, 270)
- Make sure the image dimensions match your OLED display size

### Memory Issues
- If you encounter memory issues, simplify your logo design
- Reduce the number of pixels used in your design
- Consider using text-based display instead of raw bitmap

### Display Orientation
- If the logo appears rotated, adjust the rotation in the `oled_init_kb()` function:
  ```c
  oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
      if (is_keyboard_master()) {
          return OLED_ROTATION_270;
      }
      return OLED_ROTATION_270;  // Change this value as needed
  }
  ```

## Additional Resources

- [QMK OLED Driver Documentation](https://docs.qmk.fm/#/feature_oled_driver)
- [image2cpp Tool](https://javl.github.io/image2cpp/)
- [Helix Font Editor](https://helixfonteditor.netlify.app/)
- [QMK Logo Editor](https://joric.github.io/qle/)

## Example Implementation

Here's an example of how your implementation might look in the display_oled.c file:

```c
static void render_lily58kb_logo(void) {
    static const char PROGMEM lily58kb_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,  0,  0,  0,  0,  0,  0,  0,249,249,  0,  0,255,255,  0, 56,240,128,  0,  0,  0,192,248, 56,  0,255,255,195,195,195,195,131,129,  0,  0,  0, 28,190,227,195,195,227,190, 30,  0,  0,  0,255,255,128,192,240,184, 28,  6,  3,  1,  0,255,255,195,195,195,195,195,167,190, 28,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,127,127, 96, 96, 96, 96, 96, 96,  0,127,127,  0,  0,127,127,  0,  0,  1, 15,252,240,124, 15,  1,  0,  0, 96, 96, 96, 96, 96, 96, 49, 31,  6,  0, 12, 63, 51, 96, 96, 96, 97, 51, 63, 12,  0,  0,127,127,  1,  0,  1,  7, 14, 56,112, 64,  0,127,127, 96, 96, 96, 96, 96,113, 63, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12, 12, 12,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(lily58kb_logo, sizeof(lily58kb_logo));
}

void oled_reinit_slave(void) {
    oled_init(OLED_ROTATION_270);
    oled_clear();
    oled_set_cursor(0, 0);
    render_lily58kb_logo();
}
```

This example shows how to implement the "Lily58KB" logo that displays on the slave OLED of your keyboard.
