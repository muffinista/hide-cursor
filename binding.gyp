{
  "targets": [
    {
      "target_name": "HideCursor",
      "sources": [ "src/hidecursor.cc" ],
      'cflags': [
        '-Wall',
        '-Wparentheses',
        '-Winline',
        '-Wbad-function-cast',
        '-Wdisabled-optimization',
        '-std=c++20'
      ],
      'cflags_cc': [
        '-std=c++20'
      ],
      'conditions': [
        ['OS == "mac"', {
          'sources': [
            'src/mac/hidecursor.mm'
          ],
          'include_dirs': [
            'System/Library/Frameworks/Carbon.Framework/Headers'
          ],
          'link_settings': {
            'libraries': [
              '-framework Carbon',
              '-framework AppKit',
            ]
          },
          'xcode_settings': {
            'OTHER_CFLAGS': [
                '-ObjC++',
                '-std=c++20'
            ]
          }
        }],
        ['OS == "win"', {
          'sources': [
            'src/win/hidecursor.cc'
          ],
          'msvs_settings': {
            'VCCLCompilerTool': { "ExceptionHandling": 1, 'AdditionalOptions': [ '-std:c++20' ] }
          }
        }],
        ['OS == "linux"', {
          'sources': [
            'src/unsupported/hidecursor.cc'
          ]
        }]

      ]
    }
  ]
}
