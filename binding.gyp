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
        '-Wdisabled-optimization'
      ],
      'conditions': [
        ['OS=="mac"', {
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
                '-ObjC++'
            ]
          }
        }],
        ['OS=="win"', {
          'sources': [
            'src/win/hidecursor.cc'
          ]
        }],
        ['OS=="linux"', {
          'sources': [
            'src/unsupported/hidecursor.cc'
          ]
        }]

      ]
    }
  ]
}
