import os

flags = [
        '-Wall',
        '-Wextra',
        '-Werror',
        '-Wno-long-long',
        '-Wno-variadic-macros',
        '-fexceptions',
        '-DNDEBUG',
        '-x',
        'c++',
        '-std=c++17',
        ]



def DirectoryOfThisScript():
    return os.path.dirname(os.path.abspath(__file__))


def Settings(** kwargs):
    return {
            'flags': flags,
            'include_paths_relative_to_dir': DirectoryOfThisScript()
            }

