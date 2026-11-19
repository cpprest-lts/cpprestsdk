# Releasing cpprest-lts/cpprestsdk

## Versioning

Releases continue the version numbers of microsoft/cpprestsdk, so that tools which compare versions see each release as later than every upstream one.

- Each release bumps the patch number. The first release of this fork is 2.10.20, after upstream's last release, 2.10.19.
- A patch release keeps source compatibility with 2.10.19. The shared library version stays `2.10`, and the Windows DLL names keep the `_2_10` suffix, because both come from the major and minor numbers only.
- The code holds the version as plain numbers, in `Release/CMakeLists.txt` and `Release/include/cpprest/version.h`. CMake does not accept build metadata in `project(VERSION)`, and the C++ macros are integers.
- Git tags and GitHub release names add the build metadata `+cpprest-lts`, such as `v2.10.20+cpprest-lts`. Conan and dpkg both sort `2.10.20+cpprest-lts` after `2.10.20`.

[cpprest-lts/websocketpp](https://github.com/cpprest-lts/websocketpp) follows the same scheme, starting at 0.8.4.

## Making a Release

These steps use 2.10.21 as an example.

1. If the release needs a change in cpprest-lts/websocketpp, release websocketpp first. The release commit then moves the `Release/libs/websocketpp` submodule to the commit that the websocketpp tag points to.
2. Create the branch `release/v2.10.21` from `cpprest-lts`.
3. Make the release commit "Release 2.10.21+cpprest-lts":
   - In `Release/CMakeLists.txt`, set `CPPREST_VERSION_REVISION` to 21.
   - In `Release/include/cpprest/version.h`, set `CPPREST_VERSION_REVISION` to 21.
   - At the top of `changelog.md`, add a `cpprestsdk (2.10.21+cpprest-lts)` entry for the pull requests merged since the previous release. `git log --first-parent --oneline v2.10.20+cpprest-lts..cpprest-lts` lists them.
4. Open the pull request "Release 2.10.21+cpprest-lts" against `cpprest-lts`. When CI passes, merge it with a merge commit, and delete the branch.
5. Tag the merge commit, and push the tag:
   ```sh
   git tag -a v2.10.21+cpprest-lts -m "C++ REST SDK v2.10.21+cpprest-lts" <merge commit>
   git push <remote> v2.10.21+cpprest-lts
   ```
6. Create a GitHub release from the tag, with the tag as its name, and mark it as the latest release.
7. Record the release in [issue #15](https://github.com/cpprest-lts/cpprestsdk/issues/15).
8. Update the `cpprestsdk` recipe in [conan-center-index](https://github.com/conan-io/conan-center-index) to the new version. The recipe needs the SHA-256 of the tag's source archive:
   ```sh
   curl -fsSL https://github.com/cpprest-lts/cpprestsdk/archive/refs/tags/v2.10.21+cpprest-lts.tar.gz | sha256sum
   ```

## Changelog Entry

The changelog and the GitHub release notes name the repository in each reference to an issue or pull request, such as `cpprest-lts/cpprestsdk#59` or `microsoft/cpprestsdk#1790`. GitHub links these references in both. It does not link a bare `#N` in `changelog.md`, and a bare `#N` in copied text links to the repository that it is pasted into. The entries for 2.10.19 and earlier are from microsoft/cpprestsdk, and keep its form.

The entry starts with its title, underlined so that GitHub shows it as a heading:

```
cpprestsdk (2.10.21+cpprest-lts)
--------------------------------
```

The entry groups the changes into sections, in this order: `Security:`, `Bug fixes:`, `Build:`, and `Tests, CI and documentation:`. It leaves out a section that has no changes. Each change starts with its pull request in this fork. A change longer than 110 characters continues on the next line with a two-space indent:

```
* cpprest-lts/cpprestsdk#59 Remove the port from the Host header before checking the certificate name (fixes
  microsoft/cpprestsdk#1790 and microsoft/cpprestsdk#1471)
```

The entry ends with the release date:

```
-- cpprest-lts, FRI, 6 Nov 2026
```

GitHub joins a line to the one before it unless a blank line separates them. The entry has a blank line after the underline, before each section, and before the release date.

## Release Notes

The GitHub release notes start with a paragraph that summarizes the release. It states the minimum versions of the compiler, CMake, Boost and OpenSSL, and which websocketpp release the submodule uses. The notes then list the changes under the same sections as the changelog entry, as `###` headings. Each change ends with its pull request in this fork:

```
- Remove the port from the `Host` header before checking the certificate name (cpprest-lts/cpprestsdk#59, fixes microsoft/cpprestsdk#1790 and microsoft/cpprestsdk#1471)
```
