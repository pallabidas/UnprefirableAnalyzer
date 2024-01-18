filename=dataset1.txt

cat "$filename" | while read line
do

cat>crab3_submit_JME1_${line}.py<<EOF
import sys
from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'JME1_${line}'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.allowUndistributedCMSSW = True
config.JobType.psetName = 'ConfFile_submit.py'
config.JobType.pluginName = 'Analysis'
config.JobType.outputFiles = ['histo.root']
config.JobType.maxJobRuntimeMin = 300
config.JobType.maxMemoryMB = 2500


config.Data.inputDataset = '/JetMET0/${line}/MINIAOD'

config.Data.unitsPerJob = 200000
config.Data.splitting = 'EventAwareLumiBased'
config.Data.outLFNDirBase = '/store/group/dpg_trigger/comm_trigger/L1Trigger/pdas'
config.Data.lumiMask = '/eos/user/c/cmsdqm/www/CAF/certification/Collisions23/Cert_Collisions2023_366442_370790_Golden.json'

config.Site.storageSite = 'T2_CH_CERN'
EOF

crab submit -c crab3_submit_JME1_${line}.py

done

exit 0

