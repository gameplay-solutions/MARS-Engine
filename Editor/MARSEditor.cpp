#include <MARSCore.h>

class MARSEditor : public MARS::Application
{
public:
	MARSEditor(){}
	~MARSEditor(){}
};

MARS::Application* MARS::CreateApplication()
{
	return new MARSEditor();
}