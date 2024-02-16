import FWCore.ParameterSet.Config as cms

process = cms.Process("L1Trigger")

process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '130X_dataRun3_Prompt_v4', '')

process.load('L1Trigger.Configuration.SimL1Emulator_cff')
process.load('L1Trigger.Configuration.CaloTriggerPrimitives_cff')
process.load('EventFilter.L1TXRawToDigi.caloLayer1Stage2Digis_cfi')
process.load('SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff')
process.load('CalibCalorimetry.CaloTPG.CaloTPGTranscoder_cfi')

process.simHcalTriggerPrimitiveDigis.peakFindingThreshold = 10

process.raw2digi_step = cms.Path(process.RawToDigi)
process.endjob_step = cms.EndPath(process.endOfProcess)

process.schedule = cms.Schedule(process.raw2digi_step, process.endjob_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

from L1Trigger.Configuration.customiseReEmul import L1TReEmulFromRAW
process = L1TReEmulFromRAW(process)


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
                                fileNames = cms.untracked.vstring(
                                '/store/data/Run2023B/JetMET0/MINIAOD/PromptReco-v1/000/366/469/00000/0ef12c20-c875-4204-b461-5c09936d280a.root'),
                                secondaryFileNames = cms.untracked.vstring(
                                '/store/data/Run2023B/JetMET0/RAW/v1/000/366/469/00000/c9ff9196-0d96-4c6f-88a4-06c954305e32.root'),
                            )

process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange("366469:699")

process.TFileService = cms.Service("TFileService",
                                       fileName = cms.string('histo.root')
                                   )

process.demo = cms.EDAnalyzer('UnprefirableAnalyzer',

                              )

process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.p = cms.Path(process.demo)

process.schedule.append(process.p)
