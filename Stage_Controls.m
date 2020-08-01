clear all; close all; clc;

mex -setup CPP;
mex mexfile.cpp;


function GetPosition(X, Y)
    mexfile(1);
end

function MoveAtVelocity(X, Y)
    mexfile(2, X, Y);
end

function MoveBack(X)
    mexfile(3, X);
end

function MoveForward(X)
    mexfile(4, X);
end

function MoveLeft(X)
    mexfile(5, X);
end

function MoveRelative(X, Y)
    mexfile(6, X, Y);
end

function MoveRight(X)
    mexfile(7, X);
end

function MoveToAbsolute(X, Y)
    mexfile(8, X, Y);
end

function MoveXAtVelocityUntilEncoderReference(X)
    mexfile(9, X);
end

function MoveXToAbsolute(X)
    mexfile(10, X);
end

function MoveYAtVelocityUntilEncoderReference(X)
    mexfile(11, X);
end

function MoveYToAbsolute(X)
    mexfile(12, X);
end

function RestoreReference()
    mexfile(13);
end

function SetPosition(X, Y);
    mexfile(14, X, Y);
end

function SetReference()
    mexfile(15);
end

function SkewAbout()
    mexfile(16);
end

function SkewSecond()
    mexfile(17);
end

% restoredefaultpath
% rehash toolboxcache
% savepath
