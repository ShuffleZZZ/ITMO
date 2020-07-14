module Utils
  ( concatIO
  , defaultCreationTime
  , deleteChild
  , deleteFS
  , fileSystemStructureFailReturn
  , findPathFS
  , getAllNames
  , getDirNames
  , handleFileErrors
  , helpText
  , initDirPath
  , makeFull
  , noWriteSuccessReturn
  , showDirInfoFS
  , showFileInfoFS
  , sumSize
  , updateFS
  , writeFileHS
  ) where

import Control.Monad.Trans.State (State, get)
import Data.Time.Clock (UTCTime)
import System.Directory.Tree (FileName)
import System.FilePath.Posix (joinPath, pathSeparator, splitDirectories)

import Types

-- | File info console representation.
showFileInfoFS
  :: FileEntity  -- ^ file to show information about
  -> String  -- ^ 'String' representation
showFileInfoFS file =
  feFileName file
    ++ ":\n\n"
    ++ "    path: "
    ++ fePath file
    ++ "\n"
    ++ "    permissions: "
    ++ (show $ fePermissions file)
    ++ "\n"
    ++ "    type: "
    ++ feType file
    ++ "\n"
    ++ "    creation time: "
    ++ (show $ feTime file)
    ++ "\n"
    ++ "    size: "
    ++ (show $ feSize file)
    ++ " bytes\n"

-- | Directory info console representation.
showDirInfoFS
  :: DirEntity  -- ^ directory to show information about
  -> [FileSystem] -- ^ subdirectories 'List'
  -> String  -- ^ 'String' representation
showDirInfoFS dir children =
  deFileName dir
    ++ ":\n\n"
    ++ "    size: "
    ++ (show $ sumSize children)
    ++ "\n"
    ++ "    path: "
    ++ dePath dir
    ++ "\n"
    ++ "    path: "
    ++ (show $ deFilesAmount dir)
    ++ "\n"
    ++ "    permissions: "
    ++ (show $ dePermissions dir)
    ++ " bytes\n"

-- | Calculates size of directory.
sumSize
  :: [FileSystem]  -- ^ 'List' of subdirectories and files.
  -> Integer  -- ^ bytes size
sumSize ((File x              ) : xs) = feSize x + (sumSize xs)
sumSize ((Directory _ children) : xs) = sumSize children + sumSize xs
sumSize []                            = 0

-- | Replaces content of inner file with given text.
writeFileHS
  :: String  -- ^ text to put in
  -> FileEntity  -- ^ file to change
  -> [FileSystem]  -- ^ 'FileSystem'
  -> [FileSystem]  -- ^ updated 'FileSystem'
writeFileHS text file (curFile@(File x) : xs) = do
  if fePath file == fePath x
    then
      (File $ FileEntity (feFileName file)
                         (fePath file)
                         (fePermissions file)
                         (toInteger $ 8 * length text)
                         (feType file)
                         (feTime file)
                         text
        )
        : writeFileHS text file xs
    else curFile : writeFileHS text file xs
writeFileHS text file (dir@(Directory _ _) : xs) =
  dir : writeFileHS text file xs
writeFileHS _ _ [] = []

-- | Removes file or directory from file-system.
deleteFS
  :: FileSystem  -- ^ file to remove
  -> [FileSystem]  -- ^ 'FileSystem'
  -> [FileSystem]  -- ^ updated 'FileSystem'
deleteFS file@(File fileEntity) (curFile@(File x) : xs) = do
  if fePath fileEntity == fePath x
    then deleteFS file xs
    else curFile : deleteFS file xs
deleteFS file@(File fileEntity) (dir@(Directory x children) : xs) = do
  if (joinPath $ init $ splitDirectories $ fePath fileEntity) == dePath x
    then (Directory x $ deleteChild file children) : deleteFS file xs
    else dir : deleteFS file xs
deleteFS dir@(Directory dirEntity _) (curDir@(Directory x children) : xs) = do
  if dePath dirEntity == dePath x
    then deleteFS dir xs
    else if (joinPath $ init $ splitDirectories $ dePath dirEntity) == dePath x
      then (Directory x $ deleteChild dir children) : deleteFS dir xs
      else curDir : deleteFS dir xs
deleteFS dir@(Directory _ _) (curFile@(File _) : xs) =
  curFile : deleteFS dir xs
deleteFS _ [] = []

-- | Removes file or directory from children 'List' of parent directory.
deleteChild
  :: FileSystem  -- ^ file to remove
  -> [FileSystem]  -- ^ 'FileSystem'
  -> [FileSystem]  -- ^ updated 'FileSystem'
deleteChild file@(File fileEntity) (curFile@(File x) : xs) = do
  if fePath fileEntity == fePath x
    then deleteChild file xs
    else curFile : deleteChild file xs
deleteChild dir@(Directory dirEntity _) (curDir@(Directory x _) : xs) = do
  if dePath dirEntity == dePath x
    then deleteChild dir xs
    else curDir : deleteChild dir xs
deleteChild file (x : xs) = x : deleteChild file xs
deleteChild _    []       = []

-- | Returns root path or error on fail.
initDirPath :: State (FilePath, [FileSystem]) (Maybe FilePath)
initDirPath = do
  (_, fs) <- get
  case head fs of
    Directory dirEntity _ -> pure $ Just $ dePath dirEntity
    _                     -> pure Nothing

-- | Finds Entity in 'FileSystem' by given path.
findPathFS
  :: FilePath  -- ^ absolute path
  -> [FileSystem]  -- ^ 'FyleSystem'
  -> Maybe FileSystem  -- ^ entity or 'Nothing' on fail
findPathFS path (file@(File x) : xs) =
  if fePath x == path then Just file else findPathFS path xs
findPathFS path (dir@(Directory x _) : xs) =
  if dePath x == path then Just dir else findPathFS path xs
findPathFS _ [] = Nothing

-- | Adds directory to 'FileSystem'.
updateFS
  :: FileSystem  -- ^ new directory
  -> DirEntity  -- parent directory
  -> [FileSystem]  -- ^ 'FileSystem'
  -> [FileSystem]  -- ^ updated 'FileSystem'
updateFS dir parent (file@(File _) : xs) = file : updateFS dir parent xs
updateFS dir parent (curDir@(Directory x children) : xs) =
  if dePath x == dePath parent
    then (Directory x (dir : children)) : updateFS dir parent xs
    else curDir : updateFS dir parent xs
updateFS dir _ [] = [dir]

-- | Gets all entries of directory.
getAllNames
  :: [FileSystem]  -- ^ 'List' of subdirectories and files
  -> String  -- 'String' console representation
getAllNames ((Directory x _) : xs) =
  "-<" ++ deFileName x ++ "\n" ++ getAllNames xs
getAllNames (File x : xs) = "  " ++ feFileName x ++ "\n" ++ getAllNames xs
getAllNames []            = []

-- | Returns names of all directories in given 'List'.
getDirNames
  :: [FileSystem]  -- ^ List to filter
  -> [FileName]  -- ^ 'List' of directory names
getDirNames ((Directory x _) : xs) = deFileName x : getDirNames xs
getDirNames (File _          : xs) = getDirNames xs
getDirNames []                     = []

-- | Default creation time of files for code purity.
defaultCreationTime :: UTCTime
defaultCreationTime = read "2020-05-08 15:00:00.0000000 UTC"

-- | Default return of @invoke@ functions with no return on success.
noWriteSuccessReturn :: Either String String
noWriteSuccessReturn = Right "Success"

-- | Default error on failure of current directory.
fileSystemStructureFailReturn :: Either String String
fileSystemStructureFailReturn =
  Left "Programm failed: couldn't find current directory in file-system"

-- | Translates list of relative paths to list of absolutes.
makeFull
  :: FilePath  -- ^ current directory absolute path
  -> [FilePath]  -- ^ 'List' of relative paths
  -> [FilePath]  -- ^ 'List' of absolute paths
makeFull path (x : xs) = (path ++ [pathSeparator] ++ x) : makeFull path xs
makeFull _    []       = []

-- | Informs about file read failures and returns successfully processed ones.
handleFileErrors
  :: [Either String FileSystem]  -- ^ error message or red file
  -> IO ([FileSystem])  -- ^ 'List' of processed files
handleFileErrors (Left x : xs) = do
  putStrLn x
  handleFileErrors xs
handleFileErrors (Right x : xs) = do
  rest <- handleFileErrors xs
  return $ x : rest
handleFileErrors [] = return []

-- | Transforms 'List' of IO monads to IO monad for future processing.
concatIO :: [IO [FileSystem]] -> IO [FileSystem]
concatIO (xM : xsM) = do
  x  <- xM
  xs <- concatIO xsM
  return $ x ++ xs
concatIO [] = return []

-- | Custom helper table.
helpText :: String
helpText =
  "\n\nWelcome to haskell file-system shell\n\n"
    ++ "    (c) 2020 by Glagolev Mikhail\n\n"
    ++ "Available commands:\n\n"
    ++ "    help                   -- ^ show this usage guide\n"
    ++ "    cd    <directory>      -- ^ go to directory (\"cd ..\" would move you to the parent directory)\n"
    ++ "    dir                    -- ^ show the content of current directory\n"
    ++ "    mkdir <directory-name> -- ^ create new directory in current one\n"
    ++ "    touch <file-name>      -- ^ create file in current directory\n"
    ++ "    cat   <file>           -- ^ show the content of file\n"
    ++ "    rm    <file>           -- ^ delete file\n"
    ++ "    rmdir <directory>      -- ^ delete directory and it's content\n"
    ++ "    grep  <file>           -- ^ find file in current directory or subdirectories\n"
    ++ "    echo  <file> <text>    -- ^ write text to file (overwrites previous content)\n"
    ++ "    ls    <file>           -- ^ get file information (e.g., path, access rights, type, size...)\n"
    ++ "    stat  <directory>      -- ^ get directory information (similar to \"ls <file>\")\n\n"
