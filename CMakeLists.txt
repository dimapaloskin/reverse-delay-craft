cmake_minimum_required(VERSION 3.23)

# ---------- Start main configuration ----------
set(PROJECT_NAME CRAFTING_DELAY)
set(TARGET_NAME CraftingDelay)

set(PLUGIN_CODE Crft) # A unique four-character plugin id with exactly one upper-case character
set(COMPANY_NAME "DimaPaloskin")
set(PRODUCT_NAME "Crafting Delay")
set(VERSION 0.0.1)
# ---------- End main configuration ----------


project(${PROJECT_NAME} VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/CPM.cmake)
CPMAddPackage("gh:juce-framework/JUCE#master")

juce_add_plugin(${TARGET_NAME}
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        COMPANY_NAME ${COMPANY_NAME}                # Specify the name of the plugin's author
        # IS_SYNTH TRUE/FALSE                       # Is this a synth or an effect?
        # NEEDS_MIDI_INPUT TRUE/FALSE               # Does the plugin need midi input?
        # NEEDS_MIDI_OUTPUT TRUE/FALSE              # Does the plugin need midi output?
        # IS_MIDI_EFFECT TRUE/FALSE                 # Is this plugin a MIDI effect?
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE           # Does the editor need keyboard focus?
        COPY_PLUGIN_AFTER_BUILD TRUE                # Should the plugin be installed to a default location after building?
        PLUGIN_MANUFACTURER_CODE Plsk               # A four-character manufacturer id with at least one upper-case character
        PLUGIN_CODE ${PLUGIN_CODE}                  # A unique four-character plugin id with exactly one upper-case character
        # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
        FORMATS AU VST3 Standalone                  # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
        PRODUCT_NAME ${PRODUCT_NAME})

set(JUCE_COPY_PLUGIN_AFTER_BUILD TRUE)

juce_generate_juce_header(${TARGET_NAME})

target_sources(${TARGET_NAME}
        PRIVATE
        src/PluginParameters.cpp
        src/dsp/DelayLine.cpp
        src/DSP.cpp
        src/PluginEditor.cpp
        src/PluginProcessor.cpp)

target_compile_definitions(${TARGET_NAME}
        PUBLIC
        DONT_SET_USING_JUCE_NAMESPACE=1
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${TARGET_NAME}
        PRIVATE
        # AudioPluginData           # If we'd created a binary data target, we'd link to it here

        # List of modules to link to: https://docs.juce.com/master/modules.html
        juce::juce_audio_utils
        juce::juce_audio_basics
        juce::juce_dsp
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
