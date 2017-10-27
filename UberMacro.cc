// Author: James Cowley, UCL

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "TFile.h"
#include "TSystem.h"
#include "TMacro.h"
#include "TH1.h"
#include "TAxis.h"

using namespace std;

// user defined axis ranges
Double_t ratmin = 0.6;
Double_t ratmax = 1.8;
Double_t xmin = 25;
Double_t xmax = 400;
TString histopt = ""; //"HIST ][";


void doallJZPS(string rootfile="NPCs.root"){
  doallJZ(1, 5, "logy","PS correction", "Parton_Shower_Jet_pT", "Hard_Parton_Jet_pT", "PS_correction", 0.6, 1.8);
  doverlay("NPCs.root", "PS Correction", 7, "logy");
}

void doallJZNP(){
  doallJZ(1, 5, "logy","NP correction", "Hadron_Jet_pT", "Parton_Shower_Jet_pT", "NP_correction", 0.6, 1.8);
  doverlay("NPCs.root", "NP Correction", 0, "logy");
}

void doallJZ(int minSlice=2, int maxSlice=3, string logopt="nolog", string yax="NPC", string numName="Numerator", string denName="Denominator", string ratName="Ratio", Double_t ratbot, Double_t rattop){
  cout<<"Getting histograms from JZ slices..."<<endl;

  // cross-sections and filter efficiencies from https://twiki.cern.ch/twiki/bin/view/AtlasProtected/JetStudies2012
  Double_t cros[] = {7.2850*pow(10.0,7.0), 7.2850*pow(10.0,7.0), 2.6359*pow(10.0,4.0), 5.4419*pow(10.0,2.0),
                     6.4453*pow(10.0,0.0), 3.9740*pow(10.0,-2.0), 4.1609*pow(10.0,-4.0), 4.0636*pow(10.0,-5.0)};
  Double_t filt[] = {9.8554*pow(10.0,-1.0), 1.2898*pow(10.0,-4.0), 3.9939*pow(10.0,-3.0), 1.2187*pow(10.0,-3.0),
                     7.0821*pow(10.0,-4.0), 2.1521*pow(10.0,-3.0), 4.6843*pow(10.0,-3.0), 1.4600*pow(10.0,-2.0)};

  string haddArg = "hadd -f mergedJZs.root";

  // go through all desired slices
  for(int JZi = minSlice; JZi <= maxSlice; JZi++){
    Double_t thisCros = cros[JZi];
    Double_t thisFilt = filt[JZi];
    Double_t thisWeight = thisCros/thisFilt;

    // name input and output .root files:
    std::ostringstream numStream;
    numStream << JZi;
    string inName = "rivetJZ"+numStream.str()+".root";
    string outName = "weightedJZ"+numStream.str()+".root";
    haddArg = haddArg+" "+outName;

    // get histos from file
    std::vector<TH1D*> theseHistosJZ = getHistos(inName);

    // apply scaling factor to the histograms
    cout<<"Scaling JZ histograms for "<<inName<<"..."<<endl;
    std::vector<TH1D*> theseScaledJZ = jzScale(theseHistosJZ, thisWeight);

    TFile * thisOut = new TFile(outName.c_str(), "RECREATE");
    // save scaled histograms to .root file
    for(int i = 0 ; i < theseScaledJZ.size() ; i++){
      theseScaledJZ.at(i)->Write();
    }

    thisOut->Close();
    cout<<"Saved all '"<<inName<<"' histograms to '"<<outName<<"'"<<endl;
  }

  cout<<"Merging scaled .root files with '"<<haddArg<<"'..."<<endl;
  gSystem->Exec(haddArg.c_str());
  cout<<"Performing division on mergedJZs.root..."<<endl;
  rundiv("mergedJZs.root", logopt, yax, numName, denName, ratName, ratbot, rattop);
  cout<<"Here, have your command line back."<<endl;
}

// *****************************************************************************************
//  SCALE ALL HISTOGRAMS WITHIN ROOT FILE & FLATTEN IT
// *****************************************************************************************
std::vector<TH1D*> jzScale(std::vector<TH1D*> jzHistos, Double_t fac){
  std::vector<TH1D*> output;
  for(int i = 0 ; i < jzHistos.size() ; i++){
    TH1D * thisHisto = new TH1D(*jzHistos.at(i));
    thisHisto->Scale(fac);
    output.push_back(thisHisto);
  }
  return output;
}

// *****************************************************************************************
//  FLATTEN BATCH ROOT FILES, MERGE THEM WITH HADD, THEN DIVIDE THE RESULT
// *****************************************************************************************

void doallPS(int nBatches=5){
  doall(nBatches, "nolog", "PS correction", "Parton_Shower_Jet_pT", "Hard_Parton_Jet_pT", "PS_correction", 0.6, 1.8);
  doverlayPS();
}

void doallNP(int nBatches=5){
  doall(nBatches, "nolog", "NP correction", "Hadron_Jet_pT", "Parton_Shower_Jet_pT", "NP_correction", 0.6, 1.8);
  doverlayNP();
}

void doall(int nBatches=5, string logopt="nolog", string yax="Ratio", string numName="Numerator", string denName="Denominator", string ratName="Ratio", Double_t ratbot, Double_t rattop){
  cout<<"Flattening batch .root files"<<endl;
  string haddCMD = "hadd -f Merged.root";
  for(int i = 1; i <= nBatches; i++){
    std::ostringstream name;
    name << std::setprecision(1) << std::fixed << i;
    string unflatname = "batch"+name.str()+".root";
    string flatname = "flat"+unflatname;
    flatten(unflatname, flatname);
    haddCMD = haddCMD+" "+flatname;
  }
  cout<<"Merging .root files with hadd"<<endl;
  gSystem->Exec(haddCMD.c_str());
  cout<<"Performing division on Merged.root"<<endl;
  rundiv("Merged.root", logopt, yax, numName, denName, ratName, ratbot, rattop);
  cout<<"Here, have your command line back."<<endl;
}

// *****************************************************************************************
//  SET STYLES FROM FAVOURITE OPTIONS
// *****************************************************************************************
void setMyStyle(string styleName="J"){ // default sets James style
  if(styleName == "J"){
    gROOT->LoadMacro("/home/cowleyj/macros/JamesStyle.C");
    cout<<"Setting James style..."<<endl;
    SetJamesStyle();
  }
  else if(styleName == "K"){
    gROOT->LoadMacro("/home/cowleyj/macros/KordoskyStyle.C");
    cout<<"Setting Kordosky's style..."<<endl;
    SetKordoskyStyle();
  }
  else if (styleName == "A"){
    gROOT->LoadMacro("/home/cowleyj/macros/AtlasStyle.C");
    cout<<"Setting ATLAS style..."<<endl;
    SetAtlasStyle();
  }
}

// *****************************************************************************************
//  CONVERT HISTOGRAM TO PNG AND RENAME
// *****************************************************************************************
void histopng(TH1D * hist, string imagename, string logopt="nolog", string filename="Histo_PNGs"){
  cout<<"Saving "<<imagename<<" as a PNG..."<<endl;
  TCanvas * c = new TCanvas;

  if(logopt == "logy" || logopt == "logxy"){ c->SetLogy(1); } else { c->SetLogy(0); }
  if(logopt == "logx" || logopt == "logxy"){ c->SetLogx(1); } else { c->SetLogx(0); }

  hist->Draw(histopt);
  TImage *img = TImage::Create();
  img->FromPad(c);
  imagename = filename+"/"+imagename+".png";
  const char * outname = imagename.c_str();
  img->WriteImage(outname);
  cout<<"Successfully saved "<<imagename<<"!"<<endl;
  c->Close();
}


// *****************************************************************************************
//  OVERLAY HISTOGRAM PLOTS
// *****************************************************************************************
void overlayhistoPNG(TH1D* hist1, TH1D* hist2, string logopt="nolog"){

  TH1D * h1 = new TH1D(*hist1);
  TH1D * h2 = new TH1D(*hist2);

  // create/fill draw h1
  gROOT->SetBatch();
  TCanvas *c = new TCanvas;

  // set log y axis if desired
  if(logopt == "logy" || logopt == "logxy"){ c->SetLogy(1); }
  if(logopt == "logx" || logopt == "logxy"){ c->SetLogx(1); }

  h1->SetLineColor(kRed);
  h1->TH1::GetYaxis()->SetTitle("");
  h1->Draw(histopt);
  c->Update();
  h2->SetLineColor(kBlue);
  h2->SetLineStyle(2); // dash
  h2->Draw(histopt+" same");
  c->Update();

  // get image from pad into PNG
  TImage *img = TImage::Create();
  img->FromPad(c);
  char * title1 = h1->GetTitle();
  string name1 = string(title1, strlen(title1));
  char * title2 = h2->GetTitle();
  string name2 = string(title2, strlen(title2));
  string imagename = "Overlay_PNGs/"+name1+"_on_"+name2+".png";
  const char * outname = imagename.c_str();
  img->WriteImage(outname);
  cout<<"Successfully saved "<<imagename<<"!"<<endl;
}


void doverlayPS(string rootfile="NPCs.root"){
  doverlay("NPCs.root", "PS Correction", 0); // maybe 7
}

void doverlayNP(string rootfile="NPCs.root"){
  doverlay("NPCs.root", "NP Correction", 7);
}

void doverlay(string rootfile="NPCs.root", string ratName="NPC", int offset=0, string logopt="nolog"){
  std::vector<TH1D*> inhistos = allHistos(rootfile);
  int nHistos = inhistos.size();
  int popEach = nHistos/3;

  gSystem->Exec("if [ -d Overlay_PNGs ]; then rm -r Overlay_PNGs; fi");
  gSystem->Exec("mkdir Overlay_PNGs");
  gROOT->SetBatch();

  TCanvas *bigc = new TCanvas;

  for(int i = 0 ; i < popEach ; i++){
    int numPos = i;
    int denPos = numPos + popEach + offset;
    int ratPos = numPos+2*popEach - offset;

    TH1D * numerator = inhistos.at(numPos);
    const char * numtitle = numerator->GetTitle();
    cout<<"- Numerator name = "<<string(numtitle, strlen(numtitle))<<endl;

    TH1D * denominator = inhistos.at(denPos);
    const char * dentitle = denominator->GetTitle();
    cout<<"- Denominator name = "<<string(dentitle, strlen(dentitle))<<endl;

    TH1D * ratio = inhistos.at(ratPos);
    const char * rattitle = ratio->GetTitle();
    cout<<"- Ratio name = "<<string(rattitle, strlen(rattitle))<<endl;

    overlayhistoPNG(numerator, denominator, logopt);

    // draw ratio plot with line at 1
    TCanvas *c = new TCanvas;
    ratio->SetLineColor(kRed);
    ratio->Draw(histopt);
    c->Update();
    TLine * un = new TLine(xmin,1,xmax,1);
    un->SetLineStyle(2);   // 1=solid, 2=dash, 3=dot, 4=dash-dot
    un->SetLineColor(kBlack);
    un->Draw("same");

    // get image from pad into PNG
    TImage *img = TImage::Create();
    img->FromPad(c);

    double titleY = double(i)/2;
    string titleEnd = "";
    if(titleY != 0){
      std::ostringstream titleStream;
      titleStream << std::setprecision(1) << std::fixed << titleY;
      titleEnd = "_"+titleStream.str();
    }
    string imagename = "Overlay_PNGs/"+ratName+titleEnd+".png";
    const char * outname = imagename.c_str();
    img->WriteImage(outname);
    cout<<"Successfully saved "<<imagename<<"!"<<endl;
    c->Close();

    // overlay all ratios
    ratio->SetLineColor(kBlue+4-i);
    int ls = i+1;
    while(ls > 4){ls -=4;}
    ratio->SetLineStyle(ls);  // need 2 3 or 4
    ratio->Draw(histopt+" same");
    bigc->Update();
  }

  TLine * une = new TLine(xmin,1,xmax,1); // user range
  une->SetLineStyle(2);   // 1=solid, 2=dash, 3=dot, 4=dash-dot
  une->SetLineColor(kBlack);
  une->Draw();
  bigc->Update();

  // get image from pad into PNG
  TImage *bigimg = TImage::Create();
  img->FromPad(bigc);

  string bigimagename = "Overlay_PNGs/"+ratName+"_ALL.png";
  const char * bigoutname = bigimagename.c_str();
  img->WriteImage(bigoutname);
  cout<<"Successfully saved "<<bigimagename<<"!"<<endl;
  bigc->Close();

}


// *****************************************************************************************
//  DIVIDE 2 HISTOGRAMS WITHOUT EDITING THE ORIGINALS & CHANGE TITLES
// *****************************************************************************************
TH1D * histodiv(TH1D * hist1, TH1D * hist2, string newtitle, string newytitle){

  // do division
  TH1D * result = new TH1D(*hist1);
  result->TH1::Divide(hist2);

  // make a new histogram title
  char * title1 = hist1->GetTitle();
  string rlabel = string(title1, strlen(title1));
  size_t rpos = rlabel.find(" (R");
  rlabel = rlabel.substr(rpos);
  newtitle=newtitle+rlabel;
  result->TH1::SetTitle(newtitle.c_str());

  // make a new histogram name
  char * name1 = hist1->GetName();
  string newname = string(name1, strlen(name1));
  size_t pos = newname.find("_pT");
  newname = newname.substr(pos);
  newname = "NPC"+newname;
  result->TH1::SetName(newname.c_str());

  // make a new y axis name
  result->TH1::GetYaxis()->SetTitle(newytitle.c_str());
  gROOT->ForceStyle();
  return result;
}

// *****************************************************************************************
//  TIDY UP HISTOGRAM NAMES
// *****************************************************************************************
TH1D * stripname(TH1D * hist1){
  TH1D * result = new TH1D(*hist1);
  char * name1 = result->GetName();
  string newname = string(name1, strlen(name1));
  size_t pos = newname.find("/");
  newname = newname.substr(pos+1);
  pos = newname.find("/");
  newname = newname.substr(pos+1);
  result->TH1::SetName(newname.c_str());
  return result;
}

// *****************************************************************************************
//  GET HISTOGRAMS FROM ROOT FILE & STORE IN A VECTOR
// *****************************************************************************************
std::vector<TH1D*> getHistos(string rootfile){

  // check if ROOT file exists
  // NB: AccessPathName is stupid, returns false if file found & vice versa
  bool fileFound = !gSystem->AccessPathName(rootfile.c_str());
  if(!fileFound){
    cout<<"No file '"<<rootfile<<"' found."<<endl;
    return;
  }

  TFile * theFile = new TFile(rootfile.c_str());
  TList * theList = theFile->GetListOfKeys();
  theList->Sort();
  int theListSize = theList->GetSize();

  if(theListSize == 1){ // if histos are in a TDirectory (i.e. not flat)
    cout<<"Getting histograms from ROOT file '"<<rootfile<<"'."<<endl;
    TKey * theDir = theList->At(0);
    char * theDirName = theDir->GetName();
    TDirectory * fileHistos = theFile->Get(theDirName);
    theList = fileHistos->GetListOfKeys();
    theList->Sort();
    int nHistos = theList->GetSize();
  }
  else{ // if histos are directly in the TFile (i.e. flat)
    cout<<"Getting histograms from flat ROOT file '"<<rootfile<<"'."<<endl;
    TFile * fileHistos = theFile;
    int nHistos = theListSize;
  }

  // population of each kind of histogram (hadron jet & parton jet)
  int popEach = nHistos/2;

  // initialise output collections
  std::vector<TH1D*> hadOutput, parOutput, allOutput;

  // loop over all histograms
  for(int nHad = 0 ; nHad < popEach ; nHad++){
    int nPar = nHad+popEach;
    char * hadName = theList->At(nHad)->GetName();
    char * parName = theList->At(nPar)->GetName();
    TH1D * oldHad = fileHistos->Get(hadName);
    TH1D * oldPar = fileHistos->Get(parName);
    TH1D * hadHisto = new TH1D(*oldHad);
    TH1D * parHisto = new TH1D(*oldPar);
    hadOutput.push_back(stripname(hadHisto));
    parOutput.push_back(stripname(parHisto));
  }

  // stick two collections together:
  allOutput = hadOutput;
  allOutput.insert(allOutput.end(), parOutput.begin(), parOutput.end());
  return allOutput;
}

std::vector<TH1D*> allHistos(string rootfile, int beg=1, int end=1000){

  // check if ROOT file exists
  // NB: AccessPathName is stupid, returns false if file found & vice versa
  bool fileFound = !gSystem->AccessPathName(rootfile.c_str());
  if(!fileFound){
    cout<<"No file '"<<rootfile<<"' found."<<endl;
    return;
  }

  TFile * theFile = new TFile(rootfile.c_str());
  TList * theList = theFile->GetListOfKeys();
  theList->Sort();
  int theListSize = theList->GetSize();

  if(theListSize == 1){ // if histos are in a TDirectory (i.e. not flat)
    cout<<"Getting histograms from ROOT file '"<<rootfile<<"'."<<endl;
    TKey * theDir = theList->At(0);
    char * theDirName = theDir->GetName();
    TDirectory * fileHistos = theFile->Get(theDirName);
    theList = fileHistos->GetListOfKeys();
    theList->Sort();
    int nHistos = theList->GetSize();
  }
  else{ // if histos are directly in the TFile (i.e. flat)
    cout<<"Getting histograms from flat ROOT file '"<<rootfile<<"'."<<endl;
    TFile * fileHistos = theFile;
    int nHistos = theListSize;
  }

  // initialise output collections
  std::vector<TH1D*> output;

  // loop over all histograms
  for(int i = beg-1 ; i < nHistos && i < end-1 ; i++){
    char * histName = theList->At(i)->GetName();
    TH1D * oldHist = fileHistos->Get(histName);
    TH1D * newHist = new TH1D(*oldHist);
    output.push_back(newHist);
  }

  return output;
}


// *****************************************************************************************
//  FLATTEN ROOT FILES
// *****************************************************************************************
void flatten(string rootfile, string outputname){

  // extract histos from ROOT file
  std::vector<TH1D*> inHistos = getHistos(rootfile);

  // save all histograms to a .root file
  TFile * outf = new TFile(outputname.c_str(), "RECREATE");

  for(int i = 0 ; i < inHistos.size() ; i++){
    TH1D * thisHisto = inHistos.at(i);
    stripname(thisHisto)->Write();
  }

  outf->Close();
  cout<<"Saved all histograms to '"<<outputname<<"'"<<endl;
}

void rundivPS(){
  rundiv("Rivet.root", "nolog","PS correction", "Parton_Shower_Jet_pT", "Hard_Parton_Jet_pT", "PS_correction", 0.6, 1.8);
}

void rundivNP(){
  rundiv("Rivet.root", "nolog","NP correction", "Hadron_Jet_pT", "Parton_Shower_Jet_pT", "NP_correction", 0.6, 1.8);
}

// *******************************************************************************************************
// RUN DIVISION ON A ROOT FILE
// *******************************************************************************************************
void rundiv(string rootfile="Rivet.root", string logopt="nolog", string yax="NPC", string numName="Numerator", string denName="Denominator", string ratName="Ratio", Double_t ratbot, Double_t rattop){

  // create directory for histogram PNGs
  gSystem->Exec("if [ -d Histo_PNGs ]; then rm -r Histo_PNGs; fi");
  gSystem->Exec("mkdir Histo_PNGs");
  gROOT->SetBatch(); // to prevent new canvas windows

  // extract histos from ROOT file
  std::vector<TH1D*> inHistos = getHistos(rootfile);
  std::vector<TH1D*> outHistos = inHistos;
  int popEach = inHistos.size()/2;

  // new .root file for histogram saving
  TFile * outf = new TFile("NPCs.root", "RECREATE");

  // loop over all histograms
  for(int nHad = 0 ; nHad < popEach ; nHad++){
    int nPar = nHad+popEach;
    TH1D * hadHisto = inHistos.at(nHad);
    TH1D * parHisto = inHistos.at(nPar);
    TH1D * npcHisto = histodiv(hadHisto, parHisto, yax.c_str(), yax.c_str());
    outHistos.push_back(npcHisto);
    double titleY = double(nHad)/2;
    string titleEnd = "";
    if(titleY != 0){
      std::ostringstream titleStream;
      titleStream << std::setprecision(1) << std::fixed << titleY;
      titleEnd = "_"+titleStream.str();
    }

    npcHisto->TH1::GetXaxis()->SetRangeUser(xmin,xmax);     // set custom x-axis range for ratio plots
    hadHisto->TH1::GetXaxis()->SetRangeUser(xmin,xmax);     // set custom x-axis range for numerator plots
    parHisto->TH1::GetXaxis()->SetRangeUser(xmin,xmax);     // set custom x-axis range for denominator plots

    // scale y axes
    TCanvas *can = new TCanvas();
    hadHisto->Draw();
    can->Update();
    Double_t ymax1 = gPad->GetUymax();
    parHisto->Draw();
    can->Update();
    Double_t ymax2 = gPad->GetUymax();
    Double_t ymax;
    if(ymax1 > ymax2){ ymax = ymax1; }
    else{ ymax = ymax2; }

    // set min y
    Double_t ymin = 0;
    if(logopt == "logy"){
      Double_t ymin1 = hadHisto->GetMinimum();
      Double_t ymin2 = parHisto->GetMinimum();
      if(ymin1 < ymin2){ ymin = ymin1; }
      else{ ymin = ymin2; }
      if(ymin == 0){ ymin = 1; }
    }

    npcHisto->TH1::GetYaxis()->SetRangeUser(ratbot,rattop); // set custom y-axis range for ratio plots
    hadHisto->TH1::GetYaxis()->SetRangeUser(ymin,ymax);        // set custom y-axis range for numerator plots
    parHisto->TH1::GetYaxis()->SetRangeUser(ymin,ymax);        // set custom y-axis range for denominator plots
    can->Close();

    histopng(hadHisto, numName+titleEnd, logopt);
    histopng(parHisto, denName+titleEnd, logopt);
    histopng(npcHisto, ratName+titleEnd);
    hadHisto->Write();
    parHisto->Write();
    npcHisto->Write();
  }

  cout<<"Saved histogram PNGs to directory Histo_PNGs"<<endl;
  outf->Close();
  cout<<"Saved all histograms to 'NPCs.root'"<<endl;
  gSystem->Exec("rm AutoDict*");
}



// *******************************************************************************************************
// GET COMBINED CORRECTION FACTOR NP*PS
// *******************************************************************************************************
bigdo4(){ bigdo("NP_0.4.root", "PS_0.4.root", "NPC_0.4_results");}
bigdo6(){ bigdo("NP_0.6.root", "PS_0.6.root", "NPC_0.6_results");}
bigdo7(){ bigdo("NP_0.7.root", "PS_0.7.root", "NPC_0.7_results");}

void bigdo(string hadrootfile, string parrootfile, string outputname){
  std::vector<TH1D*> hadHistos = getHistos(hadrootfile);
  std::vector<TH1D*> parHistos = getHistos(parrootfile);
  std::vector<TH1D*> outHistos;
  string ratName="Non-Perturbative Correction";
  const char * label = ratName.c_str();
  string numName="Hadron Jets";
  string denName="Hard Parton Jets";
  string logopt="nolog";

  // output
  string1 = "if [ -d "+outputname+" ]; then rm -r "+outputname+"; fi";
  gSystem->Exec(string1.c_str());
  string2 = "mkdir "+outputname;
  gSystem->Exec(string2.c_str());
  gROOT->SetBatch(); // to prevent new canvas windows
  string string3 = outputname+".root";
  TFile * outf = new TFile(string3.c_str(), "RECREATE");

  // go through histograms
  int popEach = hadHistos.size()/2;
  for(int nHad = 0 ; nHad < popEach ; nHad++){
    int nPar = nHad + popEach;
    TH1D * hadHisto = hadHistos.at(nHad);
    TH1D * parHisto = parHistos.at(nPar);
    TH1D * npcHisto = histodiv(hadHisto, parHisto, label, label);

    TH1D * numerator = hadHisto;
    const char * numtitle = numerator->GetTitle();
    cout<<">> Numerator name =   "<<string(numtitle, strlen(numtitle))<<endl;

    TH1D * denominator = parHisto;
    const char * dentitle = denominator->GetTitle();
    cout<<">> Denominator name = "<<string(dentitle, strlen(dentitle))<<endl;

    TH1D * ratio = npcHisto;
    const char * rattitle = ratio->GetTitle();
    cout<<">> Ratio name =       "<<string(rattitle, strlen(rattitle))<<endl;

    outHistos.push_back(npcHisto);
    double titleY = double(nHad)/2;
    string titleEnd = "";
    if(titleY != 0){
      std::ostringstream titleStream;
      titleStream << std::setprecision(1) << std::fixed << titleY;
      titleEnd = "_"+titleStream.str();
    }

    // scale y axes
    TCanvas *can = new TCanvas();
    hadHisto->Draw();
    can->Update();
    Double_t ymax1 = gPad->GetUymax();
    parHisto->Draw();
    can->Update();
    Double_t ymax2 = gPad->GetUymax();
    Double_t ymax;
    if(ymax1 > ymax2){ ymax = ymax1; }
    else{ ymax = ymax2; }

    // set min y
    Double_t ymin = 0;
    if(logopt == "logy"){
      Double_t ymin1 = hadHisto->GetMinimum();
      Double_t ymin2 = parHisto->GetMinimum();
      if(ymin1 < ymin2){ ymin = ymin1; }
      else{ ymin = ymin2; }
      if(ymin == 0){ ymin = 1; }
    }

    npcHisto->TH1::GetYaxis()->SetRangeUser(ratmin,ratmax); // set custom y-axis range for ratio plots
    hadHisto->TH1::GetYaxis()->SetRangeUser(ymin,ymax);        // set custom y-axis range for numerator plots
    parHisto->TH1::GetYaxis()->SetRangeUser(ymin,ymax);        // set custom y-axis range for denominator plots
    can->Close();

    histopng(hadHisto, numName+titleEnd, logopt, outputname);
    histopng(parHisto, denName+titleEnd, logopt, outputname);
    histopng(npcHisto, ratName+titleEnd, logopt, outputname);
    hadHisto->Write();
    parHisto->Write();
    npcHisto->Write();
  }

  cout<<"Saved histogram PNGs to directory "+outputname<<endl;
  outf->Close();
  cout<<"Saved all histograms to '"+outputname+"'"<<endl;
  gSystem->Exec("rm AutoDict*");


  doverlay(outputname+".root", ratName, 0, "nolog");
  string gs1 = "mv "+outputname+".root "+outputname+"/";
  gSystem->Exec(gs1.c_str());
  string gs2 = "mv Overlay_PNGs "+outputname+"/";
  gSystem->Exec(gs2.c_str());
}
