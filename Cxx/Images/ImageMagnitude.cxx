#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageMagnitude.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>

int main(int, char *[])
{
  // Create an image of a rectangle
  vtkSmartPointer<vtkImageCanvasSource2D> source = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  source->SetScalarTypeToUnsignedChar();
  source->SetNumberOfScalarComponents(3);
  source->SetExtent(0, 200, 0, 200, 0, 0);
  
  // Clear the image
  source->SetDrawColor(0,0,0);
  source->FillBox(0,200,0,200);
  
  // Draw a red box
  source->SetDrawColor(255,0,0);
  source->FillBox(100,120,100,120);
  source->Update();

  vtkSmartPointer<vtkImageMagnitude> magnitudeFilter = 
      vtkSmartPointer<vtkImageMagnitude>::New();
  magnitudeFilter->SetInputConnection(source->GetOutputPort());
  magnitudeFilter->Update();

  // Create actors
  vtkSmartPointer<vtkImageActor> colorActor =
    vtkSmartPointer<vtkImageActor>::New();
  colorActor->GetMapper()->SetInputConnection(
    source->GetOutputPort());

  vtkSmartPointer<vtkImageActor> greyscaleActor =
    vtkSmartPointer<vtkImageActor>::New();
  greyscaleActor->GetMapper()->SetInputConnection(
    magnitudeFilter->GetOutputPort());

   // Define viewport ranges
  // (xmin, ymin, xmax, ymax)
  double colorViewport[4] = {0.0, 0.0, 0.5, 1.0};
  double greyscaleViewport[4] = {0.5, 0.0, 1.0, 1.0};

  // Setup renderers
  vtkSmartPointer<vtkRenderer> colorRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  colorRenderer->SetViewport(colorViewport);
  colorRenderer->AddActor(colorActor);
  colorRenderer->ResetCamera();
  colorRenderer->SetBackground(.4, .5, .6);

  vtkSmartPointer<vtkRenderer> greyscaleRenderer =
    vtkSmartPointer<vtkRenderer>::New();
  greyscaleRenderer->SetViewport(greyscaleViewport);
  greyscaleRenderer->AddActor(greyscaleActor);
  greyscaleRenderer->ResetCamera();
  greyscaleRenderer->SetBackground(.4, .5, .7);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(600, 300);
  renderWindow->AddRenderer(colorRenderer);
  renderWindow->AddRenderer(greyscaleRenderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
