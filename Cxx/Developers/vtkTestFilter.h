#ifndef __vtkTestFilter_h
#define __vtkTestFilter_h
 
#include "vtkPolyDataAlgorithm.h"
 
class vtkTestFilter : public vtkPolyDataAlgorithm 
{
public:
  vtkTypeRevisionMacro(vtkTestFilter,vtkAlgorithm);
 
  static vtkTestFilter *New();
 
protected:
  vtkTestFilter(){}
  ~vtkTestFilter(){}
 
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
 
private:
  vtkTestFilter(const vtkTestFilter&);  // Not implemented.
  void operator=(const vtkTestFilter&);  // Not implemented.
 
};
 
#endif
