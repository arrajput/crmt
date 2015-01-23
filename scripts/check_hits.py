import ROOT
import sys

m0_s = ROOT.TH1I('m0_s','m0_s',32,0,32)
m1_s = ROOT.TH1I('m1_s','m1_s',32,0,32)
m2_s = ROOT.TH1I('m2_s','m2_s',32,0,32)
m3_s = ROOT.TH1I('m3_s','m3_s',32,0,32)

m0_t = ROOT.TH1I('m0_t','m0_t',32,0,32)
m1_t = ROOT.TH1I('m1_t','m1_t',32,0,32)
m2_t = ROOT.TH1I('m2_t','m2_t',32,0,32)
m3_t = ROOT.TH1I('m3_t','m3_t',32,0,32)

thefile  = ROOT.TFile(sys.argv[1])
simtree  = thefile.Get('SimulationTree')
mod0tree = thefile.Get('Mod0Tree')
mod1tree = thefile.Get('Mod1Tree')
mod2tree = thefile.Get('Mod2Tree')
mod3tree = thefile.Get('Mod3Tree')

for event in mod0tree:
    for hit in event.HitPinsTop0:
        m0_t.Fill(hit)
    for hit in event.HitPinsBot0:
        m0_t.Fill(hit)
for event in mod1tree:
    for hit in event.HitPinsTop1:
        m1_t.Fill(hit)
    for hit in event.HitPinsBot1:
        m1_t.Fill(hit)
for event in mod2tree:
    for hit in event.HitPinsTop2:
        m2_t.Fill(hit)
    for hit in event.HitPinsBot2:
        m2_t.Fill(hit)
for event in mod3tree:
    for hit in event.HitPinsTop3:
        m3_t.Fill(hit)
    for hit in event.HitPinsBot3:
        m3_t.Fill(hit)

for event in simtree:
    for i in xrange(len(event.PinsArray0)):
        if (event.PinsArray0[i] == 1 ):
            m0_s.Fill(i)
    for i in xrange(len(event.PinsArray1)):
        if (event.PinsArray1[i] == 1 ):
            m1_s.Fill(i)
    for i in xrange(len(event.PinsArray2)):
        if (event.PinsArray2[i] == 1 ):
            m2_s.Fill(i)
    for i in xrange(len(event.PinsArray3)):
        if (event.PinsArray3[i] == 1 ):
            m3_s.Fill(i)

m0_t.SetLineWidth(5)
m1_t.SetLineWidth(5)
m2_t.SetLineWidth(5)
m3_t.SetLineWidth(5)

m0_s.SetLineWidth(2)
m1_s.SetLineWidth(2)
m2_s.SetLineWidth(2)
m3_s.SetLineWidth(2)
            
c0 = ROOT.TCanvas('c0','c0')
m0_t.SetLineColor(ROOT.kRed)
m0_t.Draw()
m0_s.Draw('same')
c1 = ROOT.TCanvas('c1','c1')
m1_t.SetLineColor(ROOT.kRed)
m1_t.Draw()
m1_s.Draw('same')
c2 = ROOT.TCanvas('c2','c2')
m2_t.SetLineColor(ROOT.kRed)
m2_t.Draw()
m2_s.Draw('same')
c3 = ROOT.TCanvas('c3','c3')
m3_t.SetLineColor(ROOT.kRed)
m3_t.Draw()
m3_s.Draw('same')

raw_input('')
