#!/usr/bin/env luajit

--[[----------------------------------------------------------
  Audio Noise Generator

    [made after JUCE's audio tutorials]
    [http://learn.juce.com/tutorials]

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2016, Peersuasive Technologies

]]------------------------------------------------------------


local title = "Audio Noise"
local app, luce = require"luce.LApplication"(title, ...)

local function MainWindow(args)
    local app, luce = app or _G.App, luce or _G.Luce
    local wsize     = {240,100}
    local mc = luce:MainComponent("MainComponent")
    local documentWindow = luce:Document(title)
    
    local volume = luce:Slider("volume")
    volume:setRange(0.0, 0.25)
    volume:setTextBoxStyle(volume.TextEntryBoxPosition.TextBoxRight, false, 100, 20)
    volume.bounds = { 10, 10, 240, 50 }

    local audio = luce:AudioAppComponent("audio")
    audio:setAudioChannels(0, 2) -- 0 input, 2 outputs

    audio:prepareToPlay(function(samplesPerBlock, sampleRate)
        print("PREPARE TO PLAY", samplesPerBlock, sampleRate)
    end)
    audio:releaseResources(function()
        print("RELEASE RESOURCES")
    end)
    audio:getNextAudioBlock(function(startSample, numSamples, numChannels, audioSampleBuffer)
        local level   = volume.value
        local levelScale = level * 2.0
        local random  = luce:Random()
        local delayed = true
        for channel=0, numChannels-1 do
            local buf = {}
            for i=1, numSamples do
                buf[i] = random:nextFloat() * levelScale - level
            end
            audioSampleBuffer:setData(channel, 0, buf) -- AudioSampleBuffer:setData(channelNum, sampleStartIndex, *data)
        end
    end)

    app:initialised(function()
        audio:start()
    end)
    app:shutdown(function()
        audio:close()
    end)

    mc:resized(function()
        local w = mc:getWidth()-20
        volume:setSize{w, 50}
    end)

    --
    documentWindow:setBackgroundColour( luce.Colours.peru )
    
    ---
    mc:setSize(wsize)
    mc:addAndMakeVisible(volume)
    mc:addAndMakeVisible(audio)
    documentWindow:setContentOwned( mc, true )
    documentWindow:setSize(wsize)
    documentWindow:setVisible(true)
    return documentWindow
end

local function control()
end
return app:start(MainWindow) --, control)
