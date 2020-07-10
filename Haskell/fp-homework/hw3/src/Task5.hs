module Task5
  ( FS(..)

  , contents
  , getDirectory'
  , name
  , _Dir
  , _File
  ) where

import Lens.Micro (Lens', Traversal')
import System.Directory (doesDirectoryExist, doesFileExist, listDirectory)
import System.FilePath.Posix (pathSeparator, splitDirectories)
import System.IO (FilePath)

-- | File System type for tree-like representation.
data FS
  = Dir
  { _name     :: FilePath  -- ^ directory name, not path
  , _contents :: [FS]  -- ^ subdirectories
  }
  | File
  { _name     :: FilePath  -- ^ file name, not path
  } deriving (Show, Eq)

-- | Scans given 'FilePath' and creates it's representation in 'FS' type.
getDirectory'
  :: FilePath  -- ^ the 'FilePath' to scan
  -> IO FS  -- ^ 'FS' representation of 'FilePath'
getDirectory' path = do
  isDir  <- doesDirectoryExist path
  isFile <- doesFileExist path
  let shortName = (last $ splitDirectories path)
  if isDir
    then do
      children   <- listDirectory path
      childrenFS <- mapM (getDirectory' . ((path <> [pathSeparator]) <>)) children
      return $ Dir shortName childrenFS
    else if isFile
      then return $ File shortName
      else return $ error $ "Unable to scan entity: " <> path

-- | Lens for @_name@ field of 'FS'.
name :: Lens' FS FilePath
name f fs = (\name' -> fs { _name = name' }) <$> f (_name fs)

-- | Lens for @_contents@ field of 'FS'.
contents :: Traversal' FS [FS]
contents f fs@(Dir _ _) =
  (\contents' -> fs { _contents = contents' }) <$> f (_contents fs)
contents _ fs = pure fs

-- | Prism for @Dir@ constructor of 'FS'.
_Dir :: Traversal' FS FS
_Dir f dir@(Dir _ _) = f dir
_Dir _ fs            = pure fs

-- | Prism for @File@ constructor of 'FS'.
_File :: Traversal' FS FS
_File f file@(File _) = f file
_File _ fs            = pure fs
