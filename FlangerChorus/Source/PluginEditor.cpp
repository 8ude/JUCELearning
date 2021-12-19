/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KadenzeChorusAudioProcessorEditor::KadenzeChorusAudioProcessorEditor (KadenzeChorusAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 300);

    auto& params = processor.getParameters();

    //Dry Wet
    AudioParameterFloat* dryWetParameter = (AudioParameterFloat*)params.getUnchecked(0);

    mDryWetSlider.setBounds(0, 0, 100, 100);
    mDryWetSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDryWetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    //self note - here the arror operator (->) is referencing the object stored at the memory address indicated by the pointer dryWetParameter
    //some of the functions and variables referenced by these arrow operations are found in the parent classes of the AudioParameterFloat
    mDryWetSlider.setRange(dryWetParameter->range.start, dryWetParameter->range.end);
    mDryWetSlider.setValue(*dryWetParameter);
    addAndMakeVisible(mDryWetSlider);

    //self note - if i understand correctly, the elements in the square brackets of these lambda expressions reference variables+objects from the outer context for their use in the lambda.
    mDryWetSlider.onValueChange = [this, dryWetParameter] { *dryWetParameter = mDryWetSlider.getValue(); };
    mDryWetSlider.onDragStart = [dryWetParameter] {dryWetParameter->beginChangeGesture(); };
    mDryWetSlider.onDragEnd = [dryWetParameter] {dryWetParameter->endChangeGesture(); };

    //Depth
    AudioParameterFloat* depthParameter = (AudioParameterFloat*)params.getUnchecked(1);

    mDepthSlider.setBounds(100, 0, 100, 100);
    mDepthSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDepthSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDepthSlider.setRange(depthParameter->range.start, depthParameter->range.end);
    mDepthSlider.setValue(*depthParameter);
    addAndMakeVisible(mDepthSlider);

    mDepthSlider.onValueChange = [this, depthParameter] { *depthParameter = mDepthSlider.getValue(); };
    mDepthSlider.onDragStart = [depthParameter] {depthParameter->beginChangeGesture(); };
    mDepthSlider.onDragEnd = [depthParameter] {depthParameter->endChangeGesture(); };

    //Rate
    AudioParameterFloat* rateParameter = (AudioParameterFloat*)params.getUnchecked(2);

    mRateSlider.setBounds(200, 0, 100, 100);
    mRateSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mRateSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mRateSlider.setRange(rateParameter->range.start, rateParameter->range.end);
    mRateSlider.setValue(*rateParameter);
    addAndMakeVisible(mRateSlider);

    mRateSlider.onValueChange = [this, rateParameter] { *rateParameter = mRateSlider.getValue(); };
    mRateSlider.onDragStart = [rateParameter] {rateParameter->beginChangeGesture(); };
    mRateSlider.onDragEnd = [rateParameter] {rateParameter->endChangeGesture(); };

    //PhaseOffset
    AudioParameterFloat* phaseOffsetParameter = (AudioParameterFloat*)params.getUnchecked(3);

    mPhaseOffsetSlider.setBounds(300, 0, 100, 100);
    mPhaseOffsetSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mPhaseOffsetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mPhaseOffsetSlider.setRange(phaseOffsetParameter->range.start, phaseOffsetParameter->range.end);
    mPhaseOffsetSlider.setValue(*phaseOffsetParameter);
    addAndMakeVisible(mPhaseOffsetSlider);

    mPhaseOffsetSlider.onValueChange = [this, phaseOffsetParameter] { *phaseOffsetParameter = mPhaseOffsetSlider.getValue(); };
    mPhaseOffsetSlider.onDragStart = [phaseOffsetParameter] {phaseOffsetParameter->beginChangeGesture(); };
    mPhaseOffsetSlider.onDragEnd = [phaseOffsetParameter] {phaseOffsetParameter->endChangeGesture(); };

    //Feedback
    AudioParameterFloat* feedbackParameter = (AudioParameterFloat*)params.getUnchecked(4);

    mFeedbackSlider.setBounds(0, 100, 100, 100);
    mFeedbackSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mFeedbackSlider.setRange(feedbackParameter->range.start, feedbackParameter->range.end);
    mFeedbackSlider.setValue(*feedbackParameter);
    addAndMakeVisible(mFeedbackSlider);

    mFeedbackSlider.onValueChange = [this, feedbackParameter] { *feedbackParameter = mFeedbackSlider.getValue(); };
    mFeedbackSlider.onDragStart = [feedbackParameter] {feedbackParameter->beginChangeGesture(); };
    mFeedbackSlider.onDragEnd = [feedbackParameter] {feedbackParameter->endChangeGesture(); };

    //type switch

    
    AudioParameterInt* typeParameter = (AudioParameterInt*)params.getUnchecked(5);

    mType.setBounds(100, 100, 100, 30);
    mType.addItem("Chorus", 1);
    mType.addItem("Flanger", 2);
    addAndMakeVisible(mType);

    mType.onChange = [this, typeParameter] {
        typeParameter->beginChangeGesture();
        *typeParameter = mType.getSelectedItemIndex();
        typeParameter->endChangeGesture();
    };

    mType.setSelectedItemIndex(*typeParameter);
    

}

KadenzeChorusAudioProcessorEditor::~KadenzeChorusAudioProcessorEditor()
{
}

//==============================================================================
void KadenzeChorusAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("COCOA CHORUS", getLocalBounds(), juce::Justification::centred, 1);
}

void KadenzeChorusAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
