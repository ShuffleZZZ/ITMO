{-# LANGUAGE Rank2Types #-}

module Task7
  ( changeExtension
  , deleteSubdirIfEmpty
  , getAllNames
  , getPath
  , move
  ) where

import Data.List (find)
import Lens.Micro (Traversal', each, filtered, (%~), (&), (.~), (^.), (^..))
import System.FilePath.Posix (pathSeparator, replaceExtension)

import Task5 (FS(..), contents, name, _Dir)
import Task6 (contentsDirs, contentsFiles, ls)

-- | Changes extensions of files inside the 'Dir' (not recursively)
-- or changes extension of 'File' itself, depends on given 'FS'
--
-- 'File' version could be prettier,
-- but implemented with lenses according to task.
changeExtension
  :: FS  -- ^ 'FS' to change extension in
  -> String  -- ^ new extension
  -> FS  -- ^ updated 'FS'
changeExtension fs@(File _) extension =
  fs & name .~ (replaceExtension (fs ^. name) extension)
changeExtension fs@(Dir _ _) extension =
  fs & contents .~ (map (flip changeExtension extension) $ fs ^.. contentsFiles)

-- | Returns names of files and directories inside of given 'FS' recursively.
getAllNames
  :: FS  -- ^ 'FS' to return the names from
  -> [FilePath]  -- ^ list of names from given 'FS'
getAllNames fs = (fs ^. name) : fs ^.. ls <> foldr ((<>) . getAllNames)
                                                   []
                                                   (fs ^.. contentsDirs)

-- | Deletes subdirectory of given 'FS' if it exists and it's empty (non-recursive).
deleteSubdirIfEmpty
  :: FS  -- ^ 'FS' to delete empty subdirectory in
  -> FilePath  -- ^ name of subdirectory
  -> FS  -- ^ updated 'FS'
deleteSubdirIfEmpty fs subdir =
  case find (\dir -> dir ^. name == subdir && null (dir ^. contents)) subdirs of
    Just emptyDir -> fs & contents .~ filter (/= emptyDir) subdirs
    Nothing       -> fs
  where
    subdirs = fs ^.. contentsDirs

-- | Lens for descending from root with saving relative path.
move
  :: FilePath  -- ^ subdirectory short name
  -> Traversal' FS FS
move dir f parent = (_Dir . contents . each) f $ parent & contents .~ [relName]
 where
  dirFS =
    head $ parent ^.. contents . each . filtered (\fs -> fs ^. name == dir)
  relName = dirFS & name %~ ((parent ^. name <> [pathSeparator]) <>)

-- | Lens to get relative path. Depends on @move@.
getPath :: Traversal' FS FilePath
getPath f fs@(File _ ) = (name) f $ fs
getPath f fs@(Dir _ _) = (name) f $ fs & name %~ (<> [pathSeparator])
