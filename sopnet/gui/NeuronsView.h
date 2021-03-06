#ifndef SOPNET_GUI_NEURONS_VIEW_H__
#define SOPNET_GUI_NEURONS_VIEW_H__

#include <pipeline/all.h>
#include <gui/ContainerView.h>
#include <gui/HorizontalPlacing.h>
#include <gui/Signals.h>
#include <sopnet/evaluation/Errors.h>
#include <sopnet/segments/SegmentTrees.h>

class NeuronsView : public pipeline::SimpleProcessNode<> {

public:

	NeuronsView();

private:

	class PainterAssigner : public pipeline::SimpleProcessNode<> {

	public:

		PainterAssigner() {

			registerInput(_painter, "painter");
		}

		void assignTo(gui::ContainerPainter& painter) {

			updateInputs();

			painter = *_painter;
		}

	private:

		void updateOutputs() {}

		pipeline::Input<gui::ContainerPainter> _painter;
	};

	void updateOutputs();

	void onNeuronsModified(const pipeline::Modified& signal);

	void onMouseDownOnNeuron(const gui::MouseDown& signal, unsigned int neuron);

	pipeline::Input<SegmentTrees> _neurons;
	pipeline::Input<Errors>  _errors;
	pipeline::Output<unsigned int> _currentNeuron;

	boost::shared_ptr<gui::ContainerView<gui::HorizontalPlacing> > _container;

	bool _neuronsChanged;
};

#endif // SOPNET_GUI_NEURONS_VIEW_H__

