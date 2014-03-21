--[[----------------------------------------------------------------------------

  LAnimatedPosition.lua

  Luce implementation of AnimatedPosition

    @alias meta

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 

(c) 2014, Peersuasive Technologies

------------------------------------------------------------------------------]]

local luce = _G.Luce
local className = "LAnimatedPosition"
local mt = {}
function mt.ContinuousWithMomentum()
    local velocity, damping = 0, 0.92
    return {
        setFriction = function(newFriction)
            damping = 1.0 - newFriction
        end,
        releasedWithVelocity = function(pos, rel)
            velocity = rel
        end,
        getNextPosition = function(oldPos, elapsedSeconds)
            velocity = velocity*damping
            if(math.abs(velocity)<0.05)then velocity = 0 end
            return oldPos+velocity*elapsedSeconds
        end,
        isStopped = function(pos)
            return velocity == 0
        end,
    }
end

function mt.SnapToPageBoundaries()
    local targetSnapPosition = 0
    return {
        releasedWithVelocity = function(pos, rel)
            targetSnapPosition = math.floor(position + 0.5)
            if(releaseVelocity>1.0)and(targetSnapPosition<position)then
                targetSnapPosition = targetSnapPosition+1
            elseif(releaseVelocity<-1.0)and(targetSnapPosition>position)then
                targetSnapPosition = targetSnapPosition-1
            end
        end,
        getNextPosition = function(oldPos, elapsedSeconds)
            if(self:isStopped(oldPos))then return targetSnapPosition end
            local snapSpeed = 10.0
            local velocity  = (targetSnapPosition - oldPos) * snapSpeed
            local newPos    = oldPos + velocity * elapsedSeconds
            return self:isStopped(newPos) and targetSnapPosition or newPos
        end,
        isStopped = function(pos)
            return math.abs(targetSnapPosition - position) < 0.001
        end,
    }
end

local function getSpeed(last, lastPos, now, newPos)
    local elapsedSecs = math.max (0.005, (now:inSeconds() - last:inSeconds()))
    local v = (newPos - lastPos) / elapsedSecs
    return math.abs( (v>0.2) and v or 0.0 )
end

local function new(_,behaviour)
    local luce = luce
    local range = luce:Range( -math.huge, math.huge )
    local position, grabbedPos, releaseVelocity
    local self = { 
        behaviour = behaviour,
    }
    local timer = luce:Timer()

    local positionChanged_cb = nil
    function self:positionChanged(func)
        if("function"==type(func))then
            positionChanged_cb = func
        end
    end

    local function moveTo(newPos)
        local now = luce.Time:getCurrentTime()
        local releaseVelocity = getSpeed(lastDrag, position, now, newPos)
        behaviour.releasedWithVelocity (newPos, releaseVelocity);
        lastDrag = now;

        setPositionAndSendChange (newPos);
    end

    local function setPositionAndSendChange(newPosition)
        newPosition = range:clipValue(newPosition)
        if not(position == newPosition)then
            position = newPosition;
            if(positionChanged_cb)then
                positionChanged_cb(newPosition)
            end
        end
    end

    timer:timerCallback(function()
        local now = luce.Time:getCurrentTime()
        local constrain = (now:inSeconds()-lastUpdate:inSeconds())
        local elapsed = (constrain<0.001) and 0.001
                                          or ((0.020<constrain) and 0.020 or constrain)
        lastUpdate = now
        local newPos = behaviour:getNextPosition(position, elapsed)
        if (behaviour:isStopped(newPos))then
            timer:stopTimer()
        else
            timer:startTimer(1000 / 60)
        end
        setPositionAndSendChange(newPos)
    end)

    function self:setLimits(r)
        range = r
    end

    function self:beginDrag()
        grabbedPos = position
        releaseVelocity = 0
        timer:stopTimer()
    end

    function self:drag(delta)
        moveTo (grabbedPos + delta)
    end

    function self:endDrag()
        time:startTimer (1000 / 60)
    end

    function self:nudge(delta)
        time:startTimer(100)
        moveTo (position + delta);
    end

    function self:getPosition()
        return position
    end

    function self:setPosition(pos)
        timer:stopTimer();
        setPositionAndSendChange (pos);
    end

    return self
end

return setmetatable({ AnimatedPositionBehaviours = mt },{
    __call = new,
    __tostring = function()return className end,
})
