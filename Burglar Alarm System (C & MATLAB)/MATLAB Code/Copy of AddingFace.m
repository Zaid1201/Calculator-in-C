function AddingFace(nOfEach,pauseval)

tmp = dir(targetDirectory);
	fcn = @(x)ismember(x,{'.','..'});
	tmp = cellfun(fcn,{tmp.name},'UniformOutput',false);
	personNumber = nnz(~[tmp{:}])+1;
    mkdir(fullfile(targetDirectory,filesep,['Person' num2str(personNumber)]))


%%% FIGURE
fdrFig = figure('windowstyle','normal',...
	'name','RECORD FACE UNTIL BEEP; Press <ESCAPE> to Stop',...
	'units','normalized',...
	'menubar','none',...
	'position',[0.2 0.1 0.6 0.7],...
	'closerequestfcn',[],...
	'currentcharacter','0',...
	'keypressfcn',@checkForEscape);

%%% Quality Control Options
%DETECTORS: for upright faces; and for QE, Nose and Mouth
% Note: these seem to be unnecessary, and to cause capture problems.
QC.oneNose = false;
QC.oneMouth = false;
if QC.oneNose
	QC.noseDetector = vision.CascadeObjectDetector(...
		'ClassificationModel','Nose','MergeThreshold',10);
end
if QC.oneMouth
	QC.mouthDetector = vision.CascadeObjectDetector(...
		'ClassificationModel','Mouth','MergeThreshold',10);
end
% H,W of bounding box must be at least this size for a proper detection
QC.minBBSize = 30; 

% Create face detector
faceDetector = vision.CascadeObjectDetector('MergeThreshold',10);

% Number of images of each person to capture:
if nargin < 1
	nOfEach = 8;
end
%Between captured frames (allow time for movement/change):
if nargin < 2
	pauseval = 0.5;
end
% For cropping of captured faces:
bboxPad = 25;
%
captureNumber = 0;
isDone = false;
getAnother = true;

%%% START: Auto-capture/detect/train!!!
RGBFrame = snapshot(vidObj);
frameSize = size(RGBFrame);
imgAx = axes('parent',fdrFig,...
	'units','normalized',...
	'position',[0.05 0.45 0.9 0.45]);
imgHndl = imshow(RGBFrame);shg;
disp('Esc to quit!')
if ismember(refreshOption,[1,2]) && getAnother && ~isDone
	while getAnother && double(get(fdrFig,'currentCharacter')) ~= 27
		% If successful, displayFrame will contain the detection box.
		% Otherwise not.
		[displayFrame, success] = capturePreprocessDetectValidateSave;
		if success
			captureNumber = captureNumber + 1;
		end
		set(imgHndl,'CData',displayFrame);
		if captureNumber >= nOfEach
			beep;pause(0.25);beep;
			queryForNext;
		end
	end %while getAnother
end

%%% Capture is done. Now for TRAINING:
imgSet = imageSet(targetDirectory,'recursive');
if numel(imgSet) < 2
	error('streamingFaceRecognition: You must capture at least two individuals for this to work!');
end
if refreshOption ~= 3
	queryForNames;
end
if validateCapturedImages
	validateCaptured(imgSet);
end
sceneFeatures = trainStackedFaceDetector(imgSet);
end