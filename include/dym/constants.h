#ifndef _DYM_CONSTANTS_H_
#define _DYM_CONSTANTS_H_

#include <limits>

namespace dym
{
	template <typename T> static constexpr T e_v = static_cast<T>(2.718281828459045235360287471352662497757l);
	template <typename T> static constexpr T log2e_v = static_cast<T>(1.442695040888963407359924681001892137427l);
	template <typename T> static constexpr T log10e_v = static_cast<T>(0.4342944819032518276511289189166050822944l);
	template <typename T> static constexpr T pi_v = static_cast<T>(3.141592653589793238462643383279502884197l);
	template <typename T> static constexpr T sqrtpi_v = static_cast<T>(1.772453850905516027298167483341145182798l);
	template <typename T> static constexpr T inv_pi_v = static_cast<T>(0.3183098861837906715377675267450287240689l);
	template <typename T> static constexpr T inv_sqrtpi_v = static_cast<T>(0.5641895835477562869480794515607725858441l);
	template <typename T> static constexpr T tau_v = static_cast<T>(6.283185307179586476925286766559005768394l);
	template <typename T> static constexpr T sqrttau_v = static_cast<T>(2.506628274631000502415765284811045253007l);
	template <typename T> static constexpr T inv_tau_v = static_cast<T>(0.1591549430918953357688837633725143620345l);
	template <typename T> static constexpr T inv_sqrttau_v = static_cast<T>(0.3989422804014326779399460599343818684759l);
	template <typename T> static constexpr T ln2_v = static_cast<T>(0.6931471805599453094172321214581765680755l);
	template <typename T> static constexpr T ln10_v = static_cast<T>(2.302585092994045684017991454684364207601l);
	template <typename T> static constexpr T sqrt2_v = static_cast<T>(1.414213562373095048801688724209698078570l);
	template <typename T> static constexpr T inv_sqrt2_v = static_cast<T>(0.7071067811865475244008443621048490392848l);
	template <typename T> static constexpr T sqrt3_v = static_cast<T>(1.732050807568877293527446341505872366943l);
	template <typename T> static constexpr T inv_sqrt3_v = static_cast<T>(0.5773502691896257645091487805019574556476l);
	template <typename T> static constexpr T phi_v = static_cast<T>(1.618033988749894848204586834365638117720l);
	template <typename T> static constexpr T egamma_v = static_cast<T>(0.5772156649015328606065120900824024310422l);
	template <typename T> static constexpr T catalan_v = static_cast<T>(0.9159655941772190150546035149323841107741l);
	template <typename T> static constexpr T apery_v = static_cast<T>(1.202056903159594285399738161511449990765l);
	template <typename T> static constexpr T glaisher_v = static_cast<T>(1.282427129100622636875342568869791727768l);
	template <typename T> static constexpr T deg2rad_v = static_cast<T>(57.29577951308232087679815481410517033241l);
	template <typename T> static constexpr T rad2deg_v = static_cast<T>(0.01745329251994329576923690768488612713443l);
	template <typename T> static constexpr T small_v = static_cast<T>(1e-8l);
	template <typename T> static constexpr T epsilon_v = std::numeric_limits<T>::epsilon();

	static constexpr long double l_e = e_v<long double>;
	static constexpr long double l_log2e = log2e_v<long double>;
	static constexpr long double l_log10e = log10e_v<long double>;
	static constexpr long double l_pi = pi_v<long double>;
	static constexpr long double l_sqrtpi = sqrtpi_v<long double>;
	static constexpr long double l_inv_pi = inv_pi_v<long double>;
	static constexpr long double l_inv_sqrtpi = inv_sqrtpi_v<long double>;
	static constexpr long double l_tau = tau_v<long double>;
	static constexpr long double l_sqrttau = sqrttau_v<long double>;
	static constexpr long double l_inv_tau = inv_tau_v<long double>;
	static constexpr long double l_inv_sqrttau = inv_sqrttau_v<long double>;
	static constexpr long double l_ln2 = ln2_v<long double>;
	static constexpr long double l_ln10 = ln10_v<long double>;
	static constexpr long double l_sqrt2 = sqrt2_v<long double>;
	static constexpr long double l_inv_sqrt2 = inv_sqrt2_v<long double>;
	static constexpr long double l_sqrt3 = sqrt3_v<long double>;
	static constexpr long double l_inv_sqrt3 = inv_sqrt3_v<long double>;
	static constexpr long double l_phi = phi_v<long double>;
	static constexpr long double l_egamma = egamma_v<long double>;
	static constexpr long double l_catalan = catalan_v<long double>;
	static constexpr long double l_apery = apery_v<long double>;
	static constexpr long double l_glaisher = glaisher_v<long double>;
	static constexpr long double l_deg2rad = deg2rad_v<long double>;
	static constexpr long double l_rad2deg = rad2deg_v<long double>;
	static constexpr long double l_small = small_v<long double>;
	static constexpr long double l_epsilon = epsilon_v<long double>;
	
	static constexpr double d_e = e_v<double>;
	static constexpr double d_log2e = log2e_v<double>;
	static constexpr double d_log10e = log10e_v<double>;
	static constexpr double d_pi = pi_v<double>;
	static constexpr double d_sqrtpi = sqrtpi_v<double>;
	static constexpr double d_inv_pi = inv_pi_v<double>;
	static constexpr double d_inv_sqrtpi = inv_sqrtpi_v<double>;
	static constexpr double d_tau = tau_v<double>;
	static constexpr double d_sqrttau = sqrttau_v<double>;
	static constexpr double d_inv_tau = inv_tau_v<double>;
	static constexpr double d_inv_sqrttau = inv_sqrttau_v<double>;
	static constexpr double d_ln2 = ln2_v<double>;
	static constexpr double d_ln10 = ln10_v<double>;
	static constexpr double d_sqrt2 = sqrt2_v<double>;
	static constexpr double d_inv_sqrt2 = inv_sqrt2_v<double>;
	static constexpr double d_sqrt3 = sqrt3_v<double>;
	static constexpr double d_inv_sqrt3 = inv_sqrt3_v<double>;
	static constexpr double d_phi = phi_v<double>;
	static constexpr double d_egamma = egamma_v<double>;
	static constexpr double d_catalan = catalan_v<double>;
	static constexpr double d_apery = apery_v<double>;
	static constexpr double d_glaisher = glaisher_v<double>;
	static constexpr double d_deg2rad = deg2rad_v<double>;
	static constexpr double d_rad2deg = rad2deg_v<double>;
	static constexpr double d_small = small_v<double>;
	static constexpr double d_epsilon = epsilon_v<double>;

	static constexpr float f_e = e_v<float>;
	static constexpr float f_log2e = log2e_v<float>;
	static constexpr float f_log10e = log10e_v<float>;
	static constexpr float f_pi = pi_v<float>;
	static constexpr float f_sqrtpi = sqrtpi_v<float>;
	static constexpr float f_inv_pi = inv_pi_v<float>;
	static constexpr float f_inv_sqrtpi = inv_sqrtpi_v<float>;
	static constexpr float f_tau = tau_v<float>;
	static constexpr float f_sqrttau = sqrttau_v<float>;
	static constexpr float f_inv_tau = inv_tau_v<float>;
	static constexpr float f_inv_sqrttau = inv_sqrttau_v<float>;
	static constexpr float f_ln2 = ln2_v<float>;
	static constexpr float f_ln10 = ln10_v<float>;
	static constexpr float f_sqrt2 = sqrt2_v<float>;
	static constexpr float f_inv_sqrt2 = inv_sqrt2_v<float>;
	static constexpr float f_sqrt3 = sqrt3_v<float>;
	static constexpr float f_inv_sqrt3 = inv_sqrt3_v<float>;
	static constexpr float f_phi = phi_v<float>;
	static constexpr float f_egamma = egamma_v<float>;
	static constexpr float f_catalan = catalan_v<float>;
	static constexpr float f_apery = apery_v<float>;
	static constexpr float f_glaisher = glaisher_v<float>;
	static constexpr float f_deg2rad = deg2rad_v<float>;
	static constexpr float f_rad2deg = rad2deg_v<float>;
	static constexpr float f_small = small_v<float>;
	static constexpr float f_epsilon = epsilon_v<float>;
}

#endif