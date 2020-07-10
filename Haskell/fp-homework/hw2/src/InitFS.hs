module InitFS
  ( initFS
  , infiniteInput
  , parseEntry
  , scanChildren
  , scanFS
  ) where

import Control.Monad.IO.Class (liftIO)
import Control.Monad.Trans.State (StateT, evalStateT, get, put, runState)
import Options.Applicative (execParserPure, getParseResult, prefs, showHelpOnEmpty)
import System.Directory
  (canonicalizePath, doesDirectoryExist, doesFileExist, getFileSize, getModificationTime,
  getPermissions, listDirectory)
import System.FilePath.Posix (splitDirectories, takeExtension)
import System.IO (hFlush, stdout)

import Invoke
import Parser
import Types
import Utils

-- | Initialize file-system in given path and runs infinite input loop.
initFS
  :: FilePath  -- ^ 'FilePath' to initialize file-system in
  -> IO ()  -- ^ work with outer world
initFS path = do
  fs <- scanFS path
  if null fs
    then do
      putStrLn "Couldn't obtain initial directory"
      return ()
    else do
      fullPath <- canonicalizePath path
      evalStateT infiniteInput (fullPath, fs)

-- | Parse root directory and all subdirectories recursively.
scanFS
  :: FilePath  -- ^ root directory of file-system
  -> IO [FileSystem]  -- ^ returns 'List' of processed files
scanFS path = do
  initDir <- parseEntry path
  case initDir of
    Left err -> do
      putStrLn err
      return []
    Right fs -> scanChildren fs

-- | Parse given directory or file to inner format or returns error message.
parseEntry
  :: FilePath  -- ^ processing file
  -> IO (Either String FileSystem)  -- ^ error or 'FileSystem' entity
parseEntry entry = do
  isDir  <- doesDirectoryExist entry
  isFile <- doesFileExist entry
  if isDir
    then do
      path        <- canonicalizePath entry
      permissions <- getPermissions entry
      files       <- listDirectory entry
      pure $ Right $ Directory
        (DirEntity (last $ splitDirectories entry)
                   path
                   permissions
                   (length files)
        )
        []
    else if isFile
      then do
        path        <- canonicalizePath entry
        permissions <- getPermissions entry
        size        <- getFileSize entry
        time        <- getModificationTime entry
        content     <- readFile entry
        pure $ Right $ File $ FileEntity (last $ splitDirectories entry)
                                         path
                                         permissions
                                         size
                                         (takeExtension entry)
                                         time
                                         content
      else pure $ Left $ "Couldn't handle " ++ entry ++ " file"

-- | Takes 'FileSystem' entity and handle it's subdirectories recursively.
scanChildren
  :: FileSystem  -- ^ parsed entity
  -> IO [FileSystem]  -- ^ 'List' of all processed entities
scanChildren (Directory dirEntity _) = do
  entries          <- listDirectory $ dePath dirEntity
  children         <- mapM parseEntry $ makeFull (dePath dirEntity) entries
  validChildren    <- handleFileErrors children
  childrenEntities <- concatIO $ map scanChildren validChildren
  return $ Directory dirEntity validChildren : childrenEntities
scanChildren file@(File _) = return [file]

-- | Infinite loop implementation for user's input entry point.
infiniteInput :: StateT (FilePath, [FileSystem]) IO ()  -- ^ prints the current directory and work results
infiniteInput = do
  (curDir, fs) <- get
  liftIO $ putStr $ curDir ++ ">"
  _     <- liftIO $ hFlush stdout
  input <- liftIO getLine
  case
      getParseResult $ execParserPure (prefs showHelpOnEmpty) opts (words input)
    of
      Just result -> do
        let (res, (newCurDir, newFs)) = runState (invoke result) (curDir, fs)
        put (newCurDir, newFs)
        case res of
          Right "Success" -> liftIO $ putStrLn ""
          Right msg       -> liftIO $ putStrLn msg
          Left  err       -> liftIO $ putStrLn err
      Nothing -> do
        liftIO
          $ putStrLn
              "Error on user input. Check out user guide or simply check for a typos"
        liftIO $ putStrLn helpText
  infiniteInput
