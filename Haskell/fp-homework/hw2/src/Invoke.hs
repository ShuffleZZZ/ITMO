module Invoke
  ( invoke
  ) where

import Types
import Utils

import Control.Monad.Trans.State
import System.FilePath.Posix

-- | Invokes parsed command and prints the output.
invoke
  :: Command  -- ^ parsed user's command
  -> State (FilePath, [FileSystem]) (Either String String)  -- ^ resulting output
invoke HELP         = pure $ Right helpText
invoke (CD dirName) = do
  (curDir, fs) <- get
  if dirName == ".."
    then do
      root <- initDirPath
      case root of
        Nothing   -> pure $ fileSystemStructureFailReturn
        Just path -> if curDir /= path
          then do
            put (joinPath $ init $ splitDirectories curDir, fs)
            pure $ noWriteSuccessReturn
          else
            pure $ Left
              "Can't change current directory to parent of file-system root"
    else do
      case findPathFS curDir fs of
        Just curDirFS -> handleChildDescend curDirFS
        Nothing       -> pure $ fileSystemStructureFailReturn
 where
  handleChildDescend (File _) = pure $ fileSystemStructureFailReturn
  handleChildDescend (Directory _ children) = do
    (curDir, fs) <- get
    if elem dirName $ getDirNames children
      then do
        put (curDir ++ [pathSeparator] ++ dirName, fs)
        pure $ noWriteSuccessReturn
      else
        pure
        $  Left
        $  "There is no directory with name "
        ++ show dirName
        ++ " at "
        ++ curDir
invoke DIR = do
  (curDir, fs) <- get
  case findPathFS curDir fs of
    Just (Directory _ children) -> pure $ Right $ getAllNames children
    Just (File _) ->
      pure
        $ Left
        $ "\"dir\" command is showing directory content, but not files (use \"cat\" instead)"
    _ -> pure $ fileSystemStructureFailReturn
invoke (MKDIR fileName) = do
  (curDir, fs) <- get
  case findPathFS curDir fs of
    Just (Directory dirEntity _) -> do
      let newPath = curDir ++ [pathSeparator] ++ fileName
      put
        ( curDir
        , updateFS
          (Directory (DirEntity fileName newPath (dePermissions dirEntity) 0) []
          )
          dirEntity
          fs
        )
      pure $ noWriteSuccessReturn
    _ -> pure $ fileSystemStructureFailReturn

invoke (TOUCH fileName) = do
  (curDir, fs) <- get
  case findPathFS curDir fs of
    Just (Directory dirEntity _) -> do
      let newPath = curDir ++ [pathSeparator] ++ fileName
      put
        ( curDir
        , updateFS
          (File $ FileEntity fileName
                             newPath
                             (dePermissions dirEntity)
                             0
                             (takeExtension fileName)
                             defaultCreationTime
                             ""
          )
          dirEntity
          fs
        )
      pure $ noWriteSuccessReturn
    _ -> pure $ fileSystemStructureFailReturn
invoke (CAT fileName) = do
  (curDir, fs) <- get
  let filePath = curDir ++ [pathSeparator] ++ fileName
  case findPathFS filePath fs of
    Just (File file) -> pure $ Right $ feContent file
    Just (Directory _ _) ->
      pure
        $ Left
        $ "\"cat\" command is showing file content, but not directories (use \"dir\" instead)"
    _ ->
      pure $ Left "Couldn't find file in current directory, operation aborted"
invoke (RM fileName) = do
  (curDir, fs) <- get
  let filePath = curDir ++ [pathSeparator] ++ fileName
  case findPathFS filePath fs of
    Just file@(File _) -> do
      put (curDir, deleteFS file fs)
      pure $ noWriteSuccessReturn
    Just (Directory _ _) ->
      pure
        $ Left
        $ "\"rm\" command is deleting files, but not directories (use \"rmdir\" instead)"
    _ ->
      pure $ Left "Couldn't find file in current directory, operation aborted"
invoke (RMDIR fileName) = do
  (curDir, fs) <- get
  let dirPath = curDir ++ [pathSeparator] ++ fileName
  case findPathFS dirPath fs of
    Just dir@(Directory _ _) -> do
      put (curDir, deleteFS dir fs)
      pure $ noWriteSuccessReturn
    Just (File _) ->
      pure
        $ Left
        $ "\"rmdir\" command is deleting directories, but not files (use \"rm\" instead)"
    _ -> pure
      $ Left "Couldn't find directory in current directory, operation aborted"
invoke (GREP fileName) = do
  (curDir, fs) <- get
  let filePath = curDir ++ [pathSeparator] ++ fileName
  case findPathFS filePath fs of
    Just (File file) -> pure $ Right $ fePath file
    Just (Directory _ _) ->
      pure
        $ Left
        $ "\"grep\" command is searching for files, but not directories"
    _ ->
      pure $ Left "Couldn't find file in current directory, operation aborted"
invoke (ECHO fileName text) = do
  (curDir, fs) <- get
  let filePath = curDir ++ [pathSeparator] ++ fileName
  case findPathFS filePath fs of
    Just (File file) -> do
      put (curDir, writeFileHS (concat text) file fs)
      pure $ noWriteSuccessReturn
    Just (Directory _ _) ->
      pure $ Left $ "\"echo\" command writes to files, but not directories"
    _ ->
      pure $ Left "Couldn't find file in current directory, operation aborted"
invoke (LS fileName) = do
  (curDir, fs) <- get
  let filePath = curDir ++ [pathSeparator] ++ fileName
  case findPathFS filePath fs of
    Just (File file) -> do
      pure $ Right $ showFileInfoFS file
    Just (Directory _ _) ->
      pure
        $ Left
        $ "\"ls\" command shows content of file, but not directories (use \"stat\" instead)"
    _ ->
      pure $ Left "Couldn't find file in current directory, operation aborted"
invoke (STAT fileName) = do
  (curDir, fs) <- get
  let dirPath = curDir ++ [pathSeparator] ++ fileName
  case findPathFS dirPath fs of
    Just (Directory dirEntity children) -> do
      pure $ Right $ showDirInfoFS dirEntity children
    Just (File _) ->
      pure
        $ Left
        $ "\"stat\" command shows content of directory, but not files (use \"ls\" instead)"
    _ ->
      pure $ Left "Couldn't find file in current directory, operation aborted"
