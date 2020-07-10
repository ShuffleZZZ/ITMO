module Parser
  ( commandParser
  , opts
  ) where

import Options.Applicative
  (Parser, ParserInfo, argument, auto, command, helper, idm, info, many, metavar, progDesc, str,
  subparser, (<**>))

import Types

-- | Commands parser with helper.
opts :: ParserInfo Command
opts = info (commandParser <**> helper) idm

-- | Parser of file-system's user input.
commandParser :: Parser Command
commandParser = subparser
  (  command "help" (info (pure HELP) (progDesc "Usage guide"))
  <> command
       "cd"
       (info (CD <$> argument str (metavar "DIRECTORY"))
             (progDesc "Go to directory")
       )
  <> command
       "dir"
       (info (pure DIR) (progDesc "Show the content of current directory"))
  <> command
       "mkdir"
       (info (MKDIR <$> argument str (metavar "DIRECTORY"))
             (progDesc "Create directory")
       )
  <> command
       "touch"
       (info (TOUCH <$> argument str (metavar "FILE"))
             (progDesc "Create file")
       )
  <> command
       "cat"
       (info (CAT <$> argument str (metavar "FILE"))
             (progDesc "Show the content of file")
       )
  <> command
       "rm"
       (info (RM <$> argument str (metavar "FILE")) (progDesc "Remove file"))
  <> command
       "rmdir"
       (info (RMDIR <$> argument str (metavar "DIRECTORY"))
             (progDesc "Remove directory")
       )
  <> command
       "grep"
       (info (GREP <$> argument str (metavar "FILE"))
             (progDesc "Find file in current directory or subdirectories")
       )
  <> command
       "echo"
       (info
         (ECHO <$> argument str (metavar "FILE") <*> many
           (argument auto (metavar "TEXT"))
         )
         (progDesc "Write text to file")
       )
  <> command
       "ls"
       (info (LS <$> argument str (metavar "FILE"))
             (progDesc "Get file information")
       )
  <> command
       "stat"
       (info (STAT <$> argument str (metavar "DIRECTORY"))
             (progDesc "Get directory information")
       )
  )

