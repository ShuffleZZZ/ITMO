{-# LANGUAGE Rank2Types #-}

module Task6
  ( cd
  , contentsDirs
  , contentsFiles
  , file
  , ls
  ) where

import Lens.Micro (Traversal', each, filtered, (^.))

import Task5 (FS(..), contents, name, _Dir, _File)

-- | Lens to filter out the subdirectories (not recursively).
contentsDirs :: Traversal' FS FS
contentsDirs = _Dir . contents . each . _Dir

-- | Lens to filter out the files in given 'Dir' (not recursively).
contentsFiles :: Traversal' FS FS
contentsFiles = _Dir . contents . each . _File

-- | Lens for descending to subdirectory.
cd
  :: FilePath  -- ^ subdirectory short name
  -> Traversal' FS FS
cd dir = _Dir . contents . each . filtered (\fs -> fs ^. name == dir)

-- | Lens for getting names of directory contents.
ls :: Traversal' FS FilePath
ls = _Dir . contents . each . name

-- | Lens for getting 'File' name.
file
  :: FilePath  -- ^ path to file to get name of
  -> Traversal' FS String
file filePath = contentsFiles . filtered (\fs -> fs ^. name == filePath) . name
