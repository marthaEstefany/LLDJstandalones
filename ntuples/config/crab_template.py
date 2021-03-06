if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException

    from CRABClient.UserUtilities import config
    config = config()
    
    from multiprocessing import Process

    # Common configuration

    config.General.workArea           = WORKAREA
    config.General.transferLogs       = False
    config.JobType.pluginName         = 'Analysis' # PrivateMC
    config.JobType.psetName           = CMSRUNCONFIG
    #config.JobType.inputFiles         = [INPUTFILES]
    config.JobType.sendExternalFolder = True
    config.JobType.maxMemoryMB        = MAXMEM
    #config.JobType.priority           = 50 # default=10, first 10 jobs=20
    config.Data.inputDBS              = 'global'    
    config.Data.splitting             = SPLITTING # 'LumiBased' EventBased, FileBased, LumiBased (1 lumi ~= 300 events)
    config.Data.totalUnits            = NUNITS
    config.Data.publication           = False
    config.Site.storageSite           = STORESITE

    #config.Data.useParent             = True

    def submit(config):
        try:
            crabCommand('submit', config = config)
            #crabCommand('submit', config = config, dryrun=True)
        except HTTPException, hte:
            print hte.headers

    # dataset dependent configuration

    config.General.requestName = REQUESTNAME
    config.Data.unitsPerJob    = UPERJOB
    config.Data.inputDataset   = DATASET
    config.Data.outLFNDirBase  = OUTLFNBASE
    p = Process(target=submit, args=(config,))
    p.start()
    p.join()

