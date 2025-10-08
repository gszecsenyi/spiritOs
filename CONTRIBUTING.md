# Contributing to SpiritOS

Thank you for your interest in contributing to SpiritOS! This unique project bridges metaphysical concepts with practical operating system development.

## How to Contribute

### 1. Understanding the Project

Before contributing, please:
- Read the [README.md](README.md) for project overview
- Review the [Technical Design Document](docs/TDD.md) for architecture details
- Check the [API Reference](docs/API.md) for implementation specifics

### 2. Areas for Contribution

We welcome contributions in several areas:

#### Code Contributions
- **Kernel Enhancements**: Improve Soul Core, Destiny Engine, or Ephemeris Provider
- **Userland Tools**: Enhance spiroctl or create new ritual handlers
- **DSL Parser**: Implement a full expression parser for trigger conditions
- **Security**: Add sandboxing, namespaces, or cryptographic features
- **Testing**: Add unit tests, integration tests, or benchmarks

#### Documentation
- **Guides**: Write tutorials or how-to guides
- **Examples**: Create example rituals or profiles
- **API Docs**: Improve or expand API documentation
- **Translations**: Translate documentation to other languages

#### Spiritual Traditions
- **Profiles**: Add new spiritual tradition profiles
- **Triggers**: Design interesting trigger patterns
- **Calculations**: Improve astronomical accuracy

### 3. Development Process

#### Setting Up

```bash
# Clone the repository
git clone https://github.com/gszecsenyi/spiritOs.git
cd spiritOs

# Build the project
make all

# Run tests
make test
```

#### Making Changes

1. **Fork** the repository
2. **Create a branch** for your feature:
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. **Make your changes** following the coding standards below
4. **Test thoroughly**:
   ```bash
   make clean && make all && make test
   ```
5. **Commit** with clear messages:
   ```bash
   git commit -m "Add feature: description"
   ```
6. **Push** to your fork:
   ```bash
   git push origin feature/your-feature-name
   ```
7. **Create a Pull Request** with:
   - Clear description of changes
   - Reference to related issues
   - Test results

### 4. Coding Standards

#### C Code Style
- Use 4 spaces for indentation (no tabs)
- Maximum line length: 100 characters
- Use descriptive variable names
- Add comments for complex logic
- Follow existing code patterns

#### Example:
```c
/**
 * Brief description of function
 * 
 * Detailed explanation if needed
 */
int function_name(int parameter) {
    // Implementation
    return result;
}
```

#### Naming Conventions
- **Functions**: `lowercase_with_underscores`
- **Types**: `lowercase_with_underscores_t`
- **Constants**: `UPPERCASE_WITH_UNDERSCORES`
- **Structs**: `descriptive_name_t`

#### File Organization
- Header guards: `#ifndef FILENAME_H`
- Include order: system headers, then local headers
- One component per file pair (.h and .c)

### 5. Testing Requirements

All contributions should include:
- **Compilation**: Must compile without errors
- **Existing Tests**: All existing tests must pass
- **New Tests**: Add tests for new features when applicable
- **Demo**: Show working example if adding major feature

### 6. Documentation Requirements

- Update relevant documentation for code changes
- Add docstrings for new functions
- Update API.md for API changes
- Update README.md for user-facing changes

### 7. Commit Message Guidelines

Good commit messages help track changes:

```
Add feature: Brief description (50 chars or less)

More detailed explanation if needed. Wrap at 72 characters.
Explain what and why, not how.

- Bullet points are okay
- Use present tense ("Add feature" not "Added feature")
- Reference issues and PRs when relevant (#123)
```

### 8. Pull Request Process

1. Update documentation
2. Add yourself to CONTRIBUTORS.md (if first contribution)
3. Ensure all tests pass
4. Request review from maintainers
5. Address review feedback
6. Wait for merge approval

### 9. Code of Conduct

#### Our Pledge
We are committed to providing a welcoming and inclusive environment.

#### Expected Behavior
- Be respectful and considerate
- Accept constructive criticism gracefully
- Focus on what's best for the project
- Show empathy towards others

#### Unacceptable Behavior
- Harassment or discrimination
- Trolling or insulting comments
- Publishing others' private information
- Other unprofessional conduct

### 10. Spiritual Considerations

SpiritOS bridges technology and spirituality. When contributing:

- **Respect Traditions**: Be respectful of all spiritual traditions
- **Accuracy**: Strive for accuracy in spiritual/astronomical calculations
- **Inclusivity**: Support multiple spiritual perspectives
- **Documentation**: Document spiritual concepts clearly

### 11. Roadmap Alignment

Check the [Roadmap](docs/TDD.md#12-development-roadmap) to align with planned features:

- **M0** (Complete): Foundation
- **M1** (Complete): Core features
- **M2** (In Progress): Advanced features
- **M3** (Planned): Production ready

Focus contributions on current milestone goals when possible.

### 12. Getting Help

If you need help:
- **Issues**: Check existing issues or create a new one
- **Discussions**: Use GitHub Discussions for questions
- **Documentation**: Check docs/ directory
- **Examples**: Review existing code patterns

### 13. Recognition

Contributors are recognized in:
- CONTRIBUTORS.md file
- Release notes
- Project documentation

Significant contributions may be highlighted in README.md.

---

## Quick Reference

```bash
# Build and test
make clean && make all && make test

# Run demo
./demo.sh

# Check celestial state
./build/spiroctl ephemeris show

# Run kernel in QEMU
make kvm-test
```

---

Thank you for contributing to SpiritOS! Together we create a bridge between the cosmic and the computational. ✨

*May your code align with the stars*
