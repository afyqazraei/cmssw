import FWCore.ParameterSet.Config as cms

process = cms.Process("DUMP")

process.load("Geometry.MuonCommonData.testGE0XML_cfi")
process.load('FWCore.MessageService.MessageLogger_cfi')

if 'MessageLogger' in process.__dict__:
    process.MessageLogger.categories.append('G4cerr')
    process.MessageLogger.categories.append('G4cout')
    process.MessageLogger.categories.append('MuonGeom')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

process.add_(cms.ESProducer("TGeoMgrFromDdd",
        verbose = cms.untracked.bool(False),
        level   = cms.untracked.int32(14)
))


process.dump = cms.EDAnalyzer("DumpSimGeometry",
                              outputFileName = cms.untracked.string('ge0DDD.root')
)

process.p = cms.Path(process.dump)
