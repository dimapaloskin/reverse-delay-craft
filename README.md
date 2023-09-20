# juce-plugin-template

Audio plugin template using JUCE and cmake
---
Clone the repo:

```bash
git clone git@github.com:dimapaloskin/juce-plugin-template.git -b clean-start my-new-awesome-audio-plugin
```

Edit `CMakeList.txt`:
```cmake
# ---------- Start main configuration ----------
set(PROJECT_NAME JUCE_EMPTY)
set(TARGET_NAME JuceEmpty)

set(PLUGIN_CODE Tmpl) # A unique four-character plugin id with exactly one upper-case character
set(COMPANY_NAME "Dima Paloskin")
set(PRODUCT_NAME "Juce Plugin Template")
set(VERSION 0.0.1)
# ---------- End main configuration ----------
```
