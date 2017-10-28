// By James Cowley, UCL
// based on ATLAS style and Mike Kordosky's style

void SetJamesStyle(){
  gStyle->Reset();
  
  // Turn off borders
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetDrawBorder(0);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetFrameBorderSize(0);
  gStyle->SetPadBorderSize(1);
  gStyle->SetTitleBorderSize(0);
  
  // Use black & white
  // Guide to TColor values here: https://root.cern.ch/root/html/MACRO_TColor_1_c.gif
  // Primaries: 0=white, 1=black, 2=red, 3=green, 4=blue, 5=yellow
  gStyle->SetAxisColor(1, "xyz");
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameLineColor(1);
  //gStyle->SetHistFillColor(2);  // red fill
  gStyle->SetHistLineColor(2);    // 1=black lines, 2=red lines
  //gStyle->SetErrorX(0);         // turn off x error bars
  //gStyle->SetPadColor(1);
  gStyle->SetPadColor(kWhite);
  gStyle->SetStatColor(0);
  gStyle->SetStatTextColor(1);
  gStyle->SetTitleColor(1);
  gStyle->SetTitleTextColor(1);
  gStyle->SetLabelColor(1,"xyz");
  gStyle->SetFuncColor(2);  // Show functions in red
  
  // Set the size of the default canvas
  // 600x500 looks almost square
  gStyle->SetCanvasDefH(500);
  gStyle->SetCanvasDefW(600);
  gStyle->SetCanvasDefX(10);
  gStyle->SetCanvasDefY(10);

  // Fonts: Helvetica, upright, normal
  int style_label_font=42;  // font number info here: https://root.cern.ch/root/html/TAttText.html
  int style_title_font=62;
  gStyle->SetLabelFont(style_label_font,"xyz");
  gStyle->SetLabelSize(0.045,"xyz");
  gStyle->SetLabelOffset(0.015,"xyz");
  gStyle->SetStatFont(style_label_font);
  gStyle->SetTitleFont(style_label_font,"xyz");  // axis titles
  gStyle->SetTitleFont(style_title_font,"h");    // histogram title
  gStyle->SetTitleSize(0.05,"xyz");              // axis titles
  gStyle->SetTitleSize(0.05,"h");                // histogram title
  gStyle->SetTitleOffset(1.1,"x");
  gStyle->SetTitleOffset(1.2,"y");
  gStyle->SetStripDecimals(kFALSE);              // if we have 1.5 do not set 1.0 -> 1
  gStyle->SetTitleX(0.12);                       // spot where histogram title goes
  gStyle->SetTitleY(0.99);
  gStyle->SetTitleW(0.78);                       // width computed so that title is centered
  //gStyle->SetTitleAlign(xy);         // x=123 left middle right y = 123 bottom middle top

  // TGaxis::SetMaxDigits(2); // restricts number of s.f. on axes (uses standard form)

  // Set Line Widths
  gStyle->SetFrameLineWidth(2);
  gStyle->SetFuncWidth(2);
  gStyle->SetHistLineWidth(2);

  // Set all fill styles to be empty and line styles to be solid
  gStyle->SetFrameFillStyle(1001);
  gStyle->SetHistFillStyle(1001); // 0 for no fill?
  gStyle->SetFrameLineStyle(0);
  gStyle->SetHistLineStyle(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetFuncStyle(1);

  // set margins (move up and to right to make room for axis labels)
  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetPadRightMargin(0.1);

  // Set options including stat box in top right
  gStyle->SetOptDate(0);
  gStyle->SetDateX(0.01);
  gStyle->SetDateY(0.01);
  gStyle->SetOptFile(0);
  gStyle->SetOptFit(111);
  gStyle->SetOptLogx(0);
  gStyle->SetOptLogy(0);
  gStyle->SetOptLogz(0);
  gStyle->SetOptStat(0); // switch of stat box
  //gStyle->SetOptStat(1110); // no histogram title
  gStyle->SetStatFormat("6.4f");
  gStyle->SetFitFormat("6.4f");
  gStyle->SetStatStyle(0); // hollow
  //gStyle->SetStatStyle(1001); // filled
  gStyle->SetStatBorderSize(0);
  gStyle->SetStatW(0.25);
  gStyle->SetStatH(0.125);
  //gStyle->SetStatX(0.90);
  //gStyle->SetStatY(0.90);
  gStyle->SetStatX(1.0-gStyle->GetPadRightMargin()-0.02);
  gStyle->SetStatY(1.0-gStyle->GetPadTopMargin()-0.02);
  gStyle->SetOptTitle(1);

  // Set tick marks and turn off grids:
  //gStyle->SetNdivisions(1005,"xyz");
  gStyle->SetNdivisions(510,"xyz");
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetTickLength(0.02,"xyz");
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);
  gStyle->SetHistMinimumZero(kTRUE); // don't suppress zeroes
  //gStyle->SetPaperSize(TStyle::kUSLetter); // US paper size
  gStyle->SetPaperSize(TStyle::kA4);         // European paper size
  gStyle->SetPalette(1,0); // use a pretty palette for color plots
  //gStyle->SetLabelColor(1,"xyz");
  gROOT->ForceStyle();   // Force this style on all histograms
}
