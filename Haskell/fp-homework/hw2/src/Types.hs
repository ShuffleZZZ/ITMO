module Types
  ( Command(..)
  , DirEntity(..)
  , FileEntity(..)
  , FileSystem(..)
  ) where

import Data.Time.Clock (UTCTime)
import System.Directory (Permissions)
import System.Directory.Tree (FileName)

-- | Type of commands availible for user input.
data Command
  = HELP  -- ^ usage guide
  | CD FileName  -- ^ go to directory
  | DIR  -- ^ show the content of current directory
  | MKDIR FileName  -- ^ create directory
  | TOUCH FileName  -- ^ create file
  | CAT FileName  -- ^ show the content of file
  | RM FileName  -- ^ remove file
  | RMDIR FileName  -- ^ remove directory
  | GREP FileName  -- ^ find file in current directory or subdirectories
  | ECHO FileName [String]  -- ^ write text to file
  | LS FileName  -- ^ get file information
  | STAT FileName  -- ^ get directory information
  deriving (Show)

-- | Type of inner file-system.
data FileSystem
  = File FileEntity -- ^ file with properties
  | Directory DirEntity [FileSystem] -- ^ directory with proerties and 'List' of subdirectories
  deriving (Show)

-- | Inner type of file with all requiered fields.
data FileEntity = FileEntity
  { feFileName :: FileName,  -- ^ short file name
    fePath :: FilePath,  -- ^ absolute file path
    fePermissions :: Permissions,  -- ^ file's permissions
    feSize :: Integer,  -- ^ size in bytes
    feType :: String,  -- ^ file type
    feTime :: UTCTime,  -- ^ UTC-format time of creation
    feContent :: String  -- ^ 'String' representation of file's content
  } deriving (Show)

-- | Inner type of directory with all requiered fields.
data DirEntity = DirEntity
  { deFileName :: FileName,  -- ^ short directory name
    dePath :: FilePath,  -- ^ absolute directory path
    dePermissions :: Permissions,  -- ^ directories permissions
    deFilesAmount :: Int  -- ^ amount of first-level files and subdirectories
  } deriving (Show)
