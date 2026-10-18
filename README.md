# Reactor Simulation V2

A thermal reactor physics simulation in C++, built from first principles
as a learning project. Calculations follow the DOE Fundamentals Handbook,
*Nuclear Physics and Reactor Theory* (DOE-HDBK-1019), with handbook worked
examples used as test cases.

## Current features

- **Nuclide library** with thermal (0.0253 eV) cross sections and atomic masses
- **Materials** built from weight fractions (alloys) or atom ratios (molecules like H₂O),
  with atom densities computed automatically
- **Macroscopic cross sections** (Σ_a, Σ_s, Σ_f, νΣ_f) and mean free paths
- **Slowing-down power** (ξΣ_s) using the exact average logarithmic energy decrement
- **Core model** that homogenizes materials by volume fraction
- **Six-factor formula** for k_eff:
  - ✅ Thermal utilization factor (f)
  - ✅ Reproduction factor (η)
  - 🚧 Resonance escape probability (p) — in progress
  - ⬜ Fast fission factor (ε), fast and thermal non-leakage (placeholder values)

## Roadmap

- Resonance escape probability, including Doppler broadening
- Geometric buckling and non-leakage probabilities
- Point reactor kinetics using Euler's method
- Finite-difference neutron diffusion solver

## Building

Open `Reactor Simulation V2.slnx` in Visual Studio and build (C++, no external dependencies).

## References

- DOE-HDBK-1019/1-93, *Nuclear Physics and Reactor Theory*, Vols. 1 & 2
- Lamarsh, *Introduction to Nuclear Reactor Theory*
