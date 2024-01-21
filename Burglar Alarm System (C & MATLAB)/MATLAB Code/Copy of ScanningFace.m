function ScanningFace
%%% Okay, so now we should have a recognizer in place!!!
figure(fdrFig)
while double(get(fdrFig,'currentCharacter')) ~= 27 && ~isDone
	bestGuess = '?';
	RGBFrame = snapshot(vidObj);
	grayFrame = rgb2gray(RGBFrame);
	bboxes = faceDetector.step(grayFrame);
	for jj = 1:size(bboxes,1)
		if all(bboxes(jj,3:4) >= QC.minBBSize)
			thisFace = imcrop(grayFrame,bboxes(jj,:));
			if preprocessOpts.matchHistograms
				thisFace = imhistmatch(thisFace,...
					preprocessOpts.targetForHistogramAndResize);
			end
			if preprocessOpts.adjustHistograms
				thisFace = histeq(thisFace);
			end
			thisFace = imresize(thisFace,...
				size(preprocessOpts.targetForHistogramAndResize));
			%tic;
			bestGuess = myPrediction(thisFace,sceneFeatures,numel(imgSet));
			if bestGuess == 0
				bestGuess = '?';
			else
				bestGuess = imgSet(bestGuess).Description;
			end
			%tPredict = toc
			RGBFrame = 	insertObjectAnnotation(RGBFrame, 'rectangle', bboxes(jj,:), bestGuess,'FontSize',48);
            disp(bestGuess);
		end
	end
	imshow(RGBFrame,'parent',imgAx);drawnow;
	title([bestGuess '?'])
end %while

%%% Clean up:
delete(vidObj)
release(faceDetector)
delete(fdrFig)
end