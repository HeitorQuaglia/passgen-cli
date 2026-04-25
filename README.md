# passgen-cli

A command-line password generator written in C. Uses `getrandom()` (with `/dev/urandom` fallback) for cryptographically secure randomness and applies rejection sampling to avoid modulo bias.

## Build

Requires GCC and GNU Autotools.

```sh
autoreconf --install
./configure
make
```

The binary is built at `src/passgen-cli`.

## Usage

```
passgen-cli [OPTIONS]
```

Use either a preset profile or manual charset flags — not both.

### Profiles

```sh
passgen-cli --profile easy-to-read    # uppercase, lowercase, numbers, no ambiguous chars
passgen-cli --profile easy-to-speak   # uppercase, lowercase only
passgen-cli --profile hard            # all charsets including ambiguous
```

### Manual flags

```sh
passgen-cli --uppercase --lowercase --numbers --symbols
passgen-cli --uppercase --numbers --length 20
passgen-cli --lowercase --symbols --ambiguity --accentuation
```

### All options

| Flag | Short | Description |
|------|-------|-------------|
| `--length <N>` | `-l` | Password length, 8–50 (default: 12) |
| `--profile <name>` | `-p` | Preset: `easy-to-read`, `easy-to-speak`, `hard` |
| `--uppercase` | `-u` | Include uppercase letters |
| `--lowercase` | `-lo` | Include lowercase letters |
| `--numbers` | `-n` | Include numbers |
| `--symbols` | `-s` | Include symbols |
| `--ambiguity` | `-a` | Include ambiguous characters (e.g. `0`, `O`, `1`, `l`) |
| `--accentuation` | `-ac` | Include accented characters |
| `--copy-to-clipboard` | `-c` | Copy output to clipboard |
| `--quiet` | `-q` | Print only the password, no error banners |
| `--help` | `-h` | Show help |

Clipboard support: `pbcopy` on macOS, `wl-copy` / `xclip` / `xsel` on Linux.

The tool auto-detects the system locale and shows error messages in Portuguese if `LANG` starts with `pt`.
