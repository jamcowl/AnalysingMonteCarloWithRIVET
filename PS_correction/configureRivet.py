
import AthenaPoolCnvSvc.ReadAthenaPool
import os

theApp.EvtMax = 500000

loc='/unix/atlas4/martyniu/Perturb/'
head='mc12_7TeV.185491.Powheg_Pythia8_AU2_CT10_Dijet_muR1muF1_ISR_alphaSmatching.evgen.EVNT.e2613_tid0140'

svcMgr.EventSelector.InputCollections = [loc+head+'6925_00/EVNT.01406925._010552.pool.root.1',
                                         loc+head+'6920_00/EVNT.01406920._010314.pool.root.1',
                                         loc+head+'6907_00/EVNT.01406907._009655.pool.root.1',
                                         loc+head+'6905_00/EVNT.01406905._009575.pool.root.1',
                                         loc+head+'6904_00/EVNT.01406904._009513.pool.root.1',
                                         loc+head+'6897_00/EVNT.01406897._009198.pool.root.1',
                                         loc+head+'6883_00/EVNT.01406883._008489.pool.root.2',
                                         loc+head+'6883_00/EVNT.01406883._008481.pool.root.2',
                                         loc+head+'6883_00/EVNT.01406883._008477.pool.root.1',
                                         loc+head+'6882_00/EVNT.01406882._008442.pool.root.1',
                                         loc+head+'6857_00/EVNT.01406857._007182.pool.root.1',
                                         loc+head+'6857_00/EVNT.01406857._007179.pool.root.1',
                                         loc+head+'6856_00/EVNT.01406856._007109.pool.root.1',
                                         loc+head+'6855_00/EVNT.01406855._007071.pool.root.1',
                                         loc+head+'6851_00/EVNT.01406851._006879.pool.root.1',
                                         loc+head+'6847_00/EVNT.01406847._006697.pool.root.1',
                                         loc+head+'6843_00/EVNT.01406843._006498.pool.root.1',
                                         loc+head+'6843_00/EVNT.01406843._006485.pool.root.1',
                                         loc+head+'6843_00/EVNT.01406843._006478.pool.root.1',
                                         loc+head+'6842_00/EVNT.01406842._006442.pool.root.1',
                                         loc+head+'6842_00/EVNT.01406842._006431.pool.root.1',
                                         loc+head+'6840_00/EVNT.01406840._006346.pool.root.1',
                                         loc+head+'6835_00/EVNT.01406835._006098.pool.root.1',
                                         loc+head+'5267_00/EVNT.01405267._005992.pool.root.1',
                                         loc+head+'5267_00/EVNT.01405267._005965.pool.root.2',
                                         loc+head+'5265_00/EVNT.01405265._005887.pool.root.1',
                                         loc+head+'5265_00/EVNT.01405265._005869.pool.root.1',
                                         loc+head+'5265_00/EVNT.01405265._005853.pool.root.2',
                                         loc+head+'5260_00/EVNT.01405260._005635.pool.root.1',
                                         loc+head+'5259_00/EVNT.01405259._005596.pool.root.1',
                                         loc+head+'5259_00/EVNT.01405259._005593.pool.root.1',
                                         loc+head+'5259_00/EVNT.01405259._005554.pool.root.1',
                                         loc+head+'5256_00/EVNT.01405256._005450.pool.root.1',
                                         loc+head+'5256_00/EVNT.01405256._005416.pool.root.1',
                                         loc+head+'5254_00/EVNT.01405254._005313.pool.root.1',
                                         loc+head+'5254_00/EVNT.01405254._005311.pool.root.1',
                                         loc+head+'5248_00/EVNT.01405248._005014.pool.root.1',
                                         loc+head+'5238_00/EVNT.01405238._004534.pool.root.1',
                                         loc+head+'5238_00/EVNT.01405238._004527.pool.root.1',
                                         loc+head+'5237_00/EVNT.01405237._004494.pool.root.1',
                                         loc+head+'5237_00/EVNT.01405237._004473.pool.root.1',
                                         loc+head+'5231_00/EVNT.01405231._004193.pool.root.1',
                                         loc+head+'5230_00/EVNT.01405230._004143.pool.root.1',
                                         loc+head+'5230_00/EVNT.01405230._004137.pool.root.1',
                                         loc+head+'4352_00/EVNT.01404352._003837.pool.root.1',
                                         loc+head+'4343_00/EVNT.01404343._003354.pool.root.1',
                                         loc+head+'4332_00/EVNT.01404332._002830.pool.root.1',
                                         loc+head+'4332_00/EVNT.01404332._002820.pool.root.1',
                                         loc+head+'4328_00/EVNT.01404328._002641.pool.root.1',
                                         loc+head+'4328_00/EVNT.01404328._002604.pool.root.1',
                                         loc+head+'4327_00/EVNT.01404327._002576.pool.root.1',
                                         loc+head+'4325_00/EVNT.01404325._002476.pool.root.1',
                                         loc+head+'4325_00/EVNT.01404325._002461.pool.root.2',
                                         loc+head+'4325_00/EVNT.01404325._002459.pool.root.1',
                                         loc+head+'4324_00/EVNT.01404324._002427.pool.root.1',
                                         loc+head+'4324_00/EVNT.01404324._002419.pool.root.1',
                                         loc+head+'4225_00/EVNT.01404225._001488.pool.root.1',
                                         loc+head+'4225_00/EVNT.01404225._001474.pool.root.1',
                                         loc+head+'4218_00/EVNT.01404218._001111.pool.root.1',
                                         loc+head+'4202_00/EVNT.01404202._000337.pool.root.1',
                                         loc+head+'4197_00/EVNT.01404197._000082.pool.root.1',
                                         loc+head+'4197_00/EVNT.01404197._000080.pool.root.1']


from AthenaCommon.AlgSequence import AlgSequence
job = AlgSequence()
from Rivet_i.Rivet_iConf import Rivet_i
rivet = Rivet_i()

# Choose which Rivet analyses to run (just the name of the analysis)
rivet.Analyses += ['PS_correction'] # You can add to this list, ['analysis1','analysis2'] as necessary

# You need to include the path of your own analysis (location of RivetMYANALYSISNAME.so) here so Rivet will find it:
rivet.AnalysisPath = '.'
rivet.HistoFile = 'Rivet.yoda'

job += rivet

