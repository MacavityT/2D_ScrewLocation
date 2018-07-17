//

#ifndef HALFUNC_H
#define HALFUNC_H

#endif // HALFUNC_H

#include "cpp/HalconCpp.h"

using namespace Halcon;

// Procedure declarations
// External procedures
// Chapter: Graphics / Text
// Short Description: This procedure writes a text message.
void disp_message (Halcon::HTuple hv_WindowHandle, Halcon::HTuple hv_String, Halcon::HTuple hv_CoordSystem,
    Halcon::HTuple hv_Row, Halcon::HTuple hv_Column, Halcon::HTuple hv_Color, Halcon::HTuple hv_Box);
// Chapter: File
// Short Description: Get all image files under the given path
void list_image_files (Halcon::HTuple hv_ImageDirectory, Halcon::HTuple hv_Extensions,
    Halcon::HTuple hv_Options, Halcon::HTuple *hv_ImageFiles);
// Chapter: Graphics / Text
// Short Description: Set font independent of OS
void set_display_font (Halcon::HTuple hv_WindowHandle, Halcon::HTuple hv_Size, Halcon::HTuple hv_Font,
    Halcon::HTuple hv_Bold, Halcon::HTuple hv_Slant);
